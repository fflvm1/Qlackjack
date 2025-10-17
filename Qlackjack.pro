QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    aimode.cpp \
    drawcard.cpp \
    main.cpp \
    mainwindow.cpp \
    player.cpp \
    settings.cpp \
    stats.cpp \
    wallpaperassistant.cpp \
    wallpapersettings.cpp

HEADERS += \
    about.h \
    aimode.h \
    drawcard.h \
    mainwindow.h \
    player.h \
    settings.h \
    stats.h \
    wallpaperassistant.h \
    wallpapersettings.h

FORMS += \
    about.ui \
    aimode.ui \
    mainwindow.ui \
    settings.ui \
    stats.ui \
    wallpapersettings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    ../Qlackjack.pro/AndroidManifest.xml \
    ../Qlackjack.pro/build.gradle \
    ../Qlackjack.pro/gradle.properties \
    ../Qlackjack.pro/gradle/wrapper/gradle-wrapper.jar \
    ../Qlackjack.pro/gradle/wrapper/gradle-wrapper.properties \
    ../Qlackjack.pro/gradlew \
    ../Qlackjack.pro/gradlew.bat \
    ../Qlackjack.pro/res/values/libs.xml \
    ../Qlackjack.pro/res/xml/qtprovider_paths.xml \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/res/values/libs.xml \
    android/res/xml/qtprovider_paths.xml

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/../Qlackjack.pro
}
