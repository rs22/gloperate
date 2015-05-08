#include <gloperate-qt/AbstractQtMapping.h>

#include <gloperate-qt/QtOpenGLWindow.h>

#include <gloperate-qt/qt-includes-begin.h>
#include <QOpenGLContext>
#include <gloperate-qt/qt-includes-end.h>

using namespace gloperate;

namespace gloperate_qt
{

AbstractQtMapping::AbstractQtMapping(QtOpenGLWindow * window)
:   AbstractMapping()
,   m_window(window)
{
}

AbstractQtMapping::~AbstractQtMapping()
{
}

void AbstractQtMapping::processEvent(AbstractEvent * event)
{
    m_window->makeCurrent();
    mapEvent(event);
    m_window->doneCurrent();
}

} // namespace gloperate_qt

