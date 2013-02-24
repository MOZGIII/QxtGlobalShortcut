INCLUDEPATH += $${QXT_SOURCE_TREE}/include
DEPENDPATH += $${QXT_SOURCE_TREE}/include
QMAKE_RPATHDIR += $${QXT_BUILD_TREE}/lib
macx:LIBS += -F$${QXT_BUILD_TREE}/lib
LIBS += -L$${QXT_BUILD_TREE}/lib

defineTest(qxtAddLibrary) {
    INCLUDEPATH += $${QXT_SOURCE_TREE}/src/$$1
    INCLUDEPATH += $${QXT_SOURCE_TREE}/include/$$2
    DEPENDPATH += $${QXT_SOURCE_TREE}/src/$$1
    DEPENDPATH += $${QXT_SOURCE_TREE}/include/$$2
    qtAddModule($$2)
}

contains(QXT, berkeley) {
    qxtAddLibrary(berkeley, QxtBerkeley)
    QXT += core
}

contains(QXT, web) {
    qxtAddLibrary(web, QxtWeb)
    QXT += core network
    QT  += network
}

contains(QXT, widgets) {
    qxtAddLibrary(widgets, QxtWidgets)
    QXT += core
    QT  += gui widgets
}

contains(QXT, network) {
    qxtAddLibrary(network, QxtNetwork)
    QXT += core
    QT  += network
}

contains(QXT, sql) {
    qxtAddLibrary(sql, QxtSql)
    QXT += core
    QT  += sql
}

contains(QXT, core) {
    qxtAddLibrary(core, QxtCore)
}
