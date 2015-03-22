#pragma once

#include <gloperate/pipeline/AbstractPipeline.h>
#include <gloperate/pipeline/UnbufferedData.h>

namespace gloperate
{

class AbstractTargetFramebufferCapability;
class AbstractViewportCapability;
class AbstractVirtualTimeCapability;
class AbstractCameraCapability;
class AbstractProjectionCapability;
class AbstractTypedRenderTargetCapability;

}

class RasterizationStage;
class PostprocessingStage;

class PostprocessingPipeline : public gloperate::AbstractPipeline
{
public:
    PostprocessingPipeline();
    virtual ~PostprocessingPipeline();

    gloperate::AbstractTargetFramebufferCapability * targetFramebufferCapability();
    gloperate::AbstractViewportCapability * viewportCapability();
    gloperate::AbstractVirtualTimeCapability * virtualTimeCapability();
    gloperate::AbstractCameraCapability * cameraCapability();
    gloperate::AbstractProjectionCapability * projectionCapability();
    gloperate::AbstractTypedRenderTargetCapability * renderTargetCapability();

protected:
    RasterizationStage  * m_rasterization;
    PostprocessingStage * m_postprocessing;

    gloperate::UnbufferedData<gloperate::AbstractTargetFramebufferCapability *> m_targetFBO;
    gloperate::UnbufferedData<gloperate::AbstractViewportCapability *> m_viewport;
    gloperate::UnbufferedData<gloperate::AbstractVirtualTimeCapability *> m_time;
    gloperate::UnbufferedData<gloperate::AbstractCameraCapability *> m_camera;
    gloperate::UnbufferedData<gloperate::AbstractProjectionCapability *> m_projection;
    gloperate::UnbufferedData<gloperate::AbstractTypedRenderTargetCapability *> m_renderTargets;
};
