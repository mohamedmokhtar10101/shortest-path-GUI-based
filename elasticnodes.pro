QT += widgets
RC_FILE = app.rc

HEADERS += \
        edge.h \
        node.h \
        graphwidget.h \
    newer.h \
    mymap.h \
    mymapnode.h \
    binarytree.h \
    leaf.h

SOURCES += \
        edge.cpp \
        main.cpp \
        node.cpp \
        graphwidget.cpp \
    newer.cpp



# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/elasticnodes
INSTALLS += target
