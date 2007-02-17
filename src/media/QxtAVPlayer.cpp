#include <QxtAVFile.h>
#include "QxtAVPlayer.h"
#include <SDL/SDL.h>
#include <QDebug>


/**
\class QxtAVPlayer QxtAVPlayer

\ingroup media

\brief simple player using the QxtAVFile and SDL

example:
\code 
QxtAudioPlayer player;
player.play("foo.wav");
\endcode
*/

static SDL_AudioSpec 	got_spec;
static QxtAVFile * 	avfile			=NULL;
static float * 		Scope			=NULL;
static int 		FRAMES_PER_BUFFER	=44800;
float 			volume_m		=0.99;

float * QxtAVPlayer::scope()
	{
	Q_ASSERT_X(Scope,"scope","You need to call open() first");
	return Scope;
	}

QxtAVFile * QxtAVPlayer::currentFile()
	{
	return avfile;
	}

void QxtAVPlayer::play(QxtAVFile * file)
	{
	Q_ASSERT_X(Scope,"scope","You need to call open() first");
	SDL_PauseAudio (1);
	QxtAVFile * b= avfile;
	avfile=NULL;
	if(b)delete(b);

	avfile= file;
	///tell avfile to resample its output to the soundcards samplerate
	avfile->resample(got_spec.freq);	
	SDL_PauseAudio (0);
	}


void QxtAVPlayer::play(QString file)
	{
	Q_ASSERT_X(Scope,"scope","You need to call open() first");
	SDL_PauseAudio (1);
	QxtAVFile * b= avfile;
	avfile=NULL;
	if(b)delete(b);

	///intialise QxtAVFile. take care of the *2 QxtAVFile wants the amount of samples to push whereas sdl means the amount per channel
	avfile= new QxtAVFile(file,got_spec.samples*2);

	///tell avfile to resample its output to the soundcards samplerate
  	avfile->resample(got_spec.freq);	
	SDL_PauseAudio (0);
	}

void QxtAVPlayer::stop()
	{
	SDL_PauseAudio (1);
	if(!avfile)return;
	QxtAVFile * b= avfile;
	avfile=NULL;
	delete(b);
	SDL_PauseAudio (0);
	}

static void Callback (void * userData, Uint8 *stream, int size)
	{
	short *out = (short*)stream;
	long fliplen = size/sizeof(short);

	if(avfile)
		{


		if (!avfile->opened())
				{
				SDL_PauseAudio (1);
				qWarning("atemping to play not opened file, stop and eof");
				QxtAVPlayer* playa = (QxtAVPlayer *)userData;
				playa->up_fetch_eof();
				return;
				}


		///we could use the flip(short*) function of QxtAVFile, but since we need to process the samples anyway, we avoid overhead
		
		float a[fliplen*sizeof(float)];
		Q_ASSERT_X(avfile->flip(a)==fliplen,"Callback","buffersize missmatch");

		for (long i=0;i<fliplen;i++)
			{
 			*out++=(short)(a[i]*volume_m*std::numeric_limits<short>::max());
			if (i%2)Scope[i]=a[i];
			}
		}

	else
		{
		for (long i=0; i<fliplen;i++)
			{
			*out++=0;
			*out++=0; 
			Scope[i]=0.0f;
			}
		}
	}


QxtAVPlayer::QxtAVPlayer(QObject * parent):QObject(parent)
	{
	}


bool QxtAVPlayer::open(int framesPerBuffer)
	{
	FRAMES_PER_BUFFER=framesPerBuffer;
	Scope=new float[FRAMES_PER_BUFFER*sizeof(float)];

	///init sdl
	Q_ASSERT_X(SDL_Init (SDL_INIT_AUDIO)>=0,"SDL",SDL_GetError());


	///sdl lets us pass a wanted spec, and it tryes to respect that. if we let it , it will try to find a mode less you intensive though
	SDL_AudioSpec wanted_spec;

	wanted_spec.freq=48000;
	wanted_spec.format=AUDIO_S16SYS;
	wanted_spec.channels=2;
        wanted_spec.silence = 0;

	wanted_spec.samples=FRAMES_PER_BUFFER;
	wanted_spec.callback=Callback;
	wanted_spec.userdata=this;
	got_spec=wanted_spec;

	///set the second parameter to NULL, to enforce the spec above, if you encounter problems
	Q_ASSERT_X(SDL_OpenAudio (&wanted_spec, &got_spec)>=0,"SDL",SDL_GetError());

	
	///unpause
	SDL_PauseAudio (0);

	return true;
	}


QxtAVPlayer::~QxtAVPlayer()
	{
	///cleanup
// 	SDL_CloseAudio();

	if(avfile)delete(avfile);
	if(Scope)delete [] Scope;
	}



void QxtAVPlayer::up_fetch_eof()
	{
	emit(currentEof ());
	}


void QxtAVPlayer::setVolume(float v)
	{
	volume_m=v;
	if (volume_m>0.99)volume_m=0.99;
	if (volume_m<0.0)volume_m=0.0;
	}