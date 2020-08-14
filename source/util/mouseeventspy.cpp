#include "mouseeventspy.h"
#include <QQmlEngine>
#include <QJSEngine>
#include <QEvent>
#include <QGuiApplication>

MouseEventSpy::MouseEventSpy(QObject *parent) : QObject(parent)
{
    qDebug() << "created Instance";
}

// This implements the SINGLETON PATTERN (*usually evil*)
// so you can get the instance in C++
MouseEventSpy* MouseEventSpy::instance()
{
    static MouseEventSpy* inst;
    if (inst == nullptr)
    {
        // If no instance has been created yet, creat a new and install it as event filter.
        // Uppon first use of the instance, it will automatically
        // install itself in the QGuiApplication
        inst = new MouseEventSpy();
        QGuiApplication* app = qGuiApp;
        app->installEventFilter(inst);
    }
    return inst;
}

// This is the method to fullfill the signature required by
// qmlRegisterSingletonType.
QObject* MouseEventSpy::singletonProvider(QQmlEngine *, QJSEngine *)
{
    return MouseEventSpy::instance();
}

// This is the method is necessary for 'installEventFilter'
bool MouseEventSpy::eventFilter(QObject* watched, QEvent* event)
{
    /*
     * (t == QEvent::MouseButtonDblClick
         || t == QEvent::MouseButtonPress
         || t == QEvent::MouseMove)
    */
    QEvent::Type t = event->type();
    if (t == QEvent::MouseButtonRelease || t == QEvent::TouchEnd)
        emit mouseEventDetected();

    return QObject::eventFilter(watched, event);
}
