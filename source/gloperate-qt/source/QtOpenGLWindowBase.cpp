#include "gloperate-qt/QtOpenGLWindowBase.h"

#include <gloperate-qt/qt-includes-begin.h>
#include <QDebug>
#include <QEvent>
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QOpenGLWidget>
#include <QVBoxLayout>
#include <gloperate-qt/qt-includes-end.h>


namespace gloperate_qt
{

class QtOpenGLWindowBasePrivate : public QOpenGLWidget
{
public:
    QtOpenGLWindowBasePrivate(QtOpenGLWindowBase * parent);

    void setUninitialized();

protected:
    void paintGL() override;
    void resizeGL(int w, int h) override;

    void initialize();

private:
    QtOpenGLWindowBase * m_parent;
    bool m_initialized;
};

QtOpenGLWindowBasePrivate::QtOpenGLWindowBasePrivate(QtOpenGLWindowBase * parent)
:   QOpenGLWidget(parent)
,   m_parent(parent)
,   m_initialized(false)
{
}

void QtOpenGLWindowBasePrivate::setUninitialized()
{
    m_initialized = false;
}

void QtOpenGLWindowBasePrivate::initialize()
{
    m_parent->onInitialize();
    m_initialized = true;
}

void QtOpenGLWindowBasePrivate::paintGL()
{
    if (!m_initialized)
        initialize();

    m_parent->onPaint();
}

void QtOpenGLWindowBasePrivate::resizeGL(int w, int h)
{
    if (!m_initialized)
        initialize();

    m_parent->onResize(w * devicePixelRatio(), h * devicePixelRatio());
}

/**
*  @brief
*    Get default OpenGL format
*/
QSurfaceFormat QtOpenGLWindowBase::defaultFormat()
{
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CoreProfile);
    #ifndef NDEBUG
        format.setOption(QSurfaceFormat::DebugContext);
    #endif
    return format;
}

/**
*  @brief
*    Constructor
*/
QtOpenGLWindowBase::QtOpenGLWindowBase(QWidget * parent)
:   QWidget(parent)
,   m_private(new QtOpenGLWindowBasePrivate(this))
{
    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_private);

    // if (f.version().first < 3)
    // {
    //     m_context->setFormat(f);
    //     if (!m_context->create()) {
    //         qDebug() << "Could not create intermediate OpenGL context.";
    //         QApplication::quit();
    //     } else {
    //         QSurfaceFormat intermediateFormat = m_context->format();
    //         qDebug().nospace() << "Created intermediate OpenGL context " << intermediateFormat.version().first << "." << intermediateFormat.version().second;

    //         if ((intermediateFormat.version().first == 3 && intermediateFormat.version().second == 0) || intermediateFormat.version().first < 3)
    //         {
    //             f.setMajorVersion(3);
    //             f.setMinorVersion(2);
    //             f.setProfile(QSurfaceFormat::CoreProfile);
    //         }
    //     }
    // }

    // m_context->setFormat(f);
    // if (!m_context->create()) {
    //     qDebug() << "Could not create OpenGL context.";
    //     QApplication::quit();
    // } else {
    //     qDebug().nospace() << "Created OpenGL context " << m_context->format().version().first << "." << m_context->format().version().second;
    // }
}

/**
*  @brief
*    Destructor
*/
QtOpenGLWindowBase::~QtOpenGLWindowBase() = default;

/**
*  @brief
*    Get OpenGL context
*/
QOpenGLContext * QtOpenGLWindowBase::context() const
{
    return m_private->context();
}
    
/**
*  @brief
*    Request update (repaint) of the window
*/
void QtOpenGLWindowBase::updateGL()
{
    m_private->update();
}

void QtOpenGLWindowBase::makeCurrent()
{
    m_private->makeCurrent();
}

void QtOpenGLWindowBase::doneCurrent()
{
    m_private->doneCurrent();
}

unsigned int QtOpenGLWindowBase::defaultFramebufferObject() const
{
    return m_private->defaultFramebufferObject();
}

void QtOpenGLWindowBase::onInitialize()
{
}

void QtOpenGLWindowBase::onResize(int w, int h)
{
}

void QtOpenGLWindowBase::onPaint()
{
}

bool QtOpenGLWindowBase::event(QEvent * event)
{
    switch (event->type()) 
    {
        case QEvent::Enter:
            enterEvent(event);
            return true;
        case QEvent::Leave:
            leaveEvent(event);
            return true;
        default:
            return QWidget::event(event);
    }
}

void QtOpenGLWindowBase::enterEvent(QEvent * /* event */)
{
}

void QtOpenGLWindowBase::leaveEvent(QEvent * /* event */)
{
}

void QtOpenGLWindowBase::setUninitialized()
{
    m_private->setUninitialized();
}

} // namespace gloperate-qt
