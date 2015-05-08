#pragma once

#include <gloperate-qt/qt-includes-begin.h>

#include <QWidget>

#include <gloperate-qt/qt-includes-end.h>
#include <gloperate-qt/gloperate-qt_api.h>


class QSurfaceFormat;
class QOpenGLContext;


namespace gloperate_qt
{

class QtOpenGLWindowBasePrivate;

/**
*  @brief
*    Qt window that initializes an OpenGL context for rendering
*
*  @remarks
*    This base class is for general use of OpenGL and does not depend on
*    using gloperate for rendering. When using gloperate, the derived
*    class QtOpenGLWindow should be used.
*/
class GLOPERATE_QT_API QtOpenGLWindowBase : public QWidget
{
public:
    /**
    *  @brief
    *    Get default OpenGL format
    *
    *  @return
    *    Surface format
    */
    static QSurfaceFormat defaultFormat();

public:
    /**
    *  @brief
    *    Constructor
    */
    QtOpenGLWindowBase(QWidget * parent = nullptr);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~QtOpenGLWindowBase();

    /**
    *  @brief
    *    Get OpenGL context
    *
    *  @return
    *    OpenGL context
    */
    QOpenGLContext * context() const;

    /**
    *  @brief
    *    Request update (repaint) of the window
    */
    void updateGL();

	void makeCurrent();
	void doneCurrent();
    
    unsigned int defaultFramebufferObject() const;

protected:
    virtual void onInitialize();
    virtual void onResize(int w, int h);
    virtual void onPaint();

    virtual bool event(QEvent * event) override;
    virtual void enterEvent(QEvent * event);
    virtual void leaveEvent(QEvent * event);

protected:
    void setUninitialized();

protected:
    friend class QtOpenGLWindowBasePrivate;
    QtOpenGLWindowBasePrivate * m_private;
};

} // namespace gloperate-qt
