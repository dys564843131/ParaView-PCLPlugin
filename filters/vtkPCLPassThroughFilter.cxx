#include "vtkPCLPassThroughFilter.h"
#include "vtkPCLConversions.h"
#include "_PCLInvokeWithPointType.h"

#include <pcl/filters/passthrough.h>

vtkStandardNewMacro(vtkPCLPassThroughFilter);

//----------------------------------------------------------------------------
vtkPCLPassThroughFilter::vtkPCLPassThroughFilter()
{
  this->SetNumberOfInputPorts(1);
  this->SetNumberOfOutputPorts(1);
  this->FieldName = "x";
  this->Limits[0] = 0.0;
  this->Limits[1] = 1.0;
  this->Invert = false;
}

//----------------------------------------------------------------------------
vtkPCLPassThroughFilter::~vtkPCLPassThroughFilter()
{
}

//----------------------------------------------------------------------------
void vtkPCLPassThroughFilter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//----------------------------------------------------------------------------
int vtkPCLPassThroughFilter::ApplyPCLFilter(
  vtkSmartPointer<vtkPolyData> & input,
  vtkSmartPointer<vtkPolyData> & output
)
{
  INVOKE_WITH_POINT_TYPE(this->InternalApplyPCLFilter, input, output);
  return 1;
}

//----------------------------------------------------------------------------
template <typename PointType>
void vtkPCLPassThroughFilter::InternalApplyPCLFilter(
  vtkSmartPointer<vtkPolyData> & input,
  vtkSmartPointer<vtkPolyData> & output
)
{
  typedef pcl::PointCloud<PointType> CloudT;
  typename CloudT::Ptr inputCloud(new CloudT);
  typename CloudT::Ptr outputCloud(new CloudT);

  vtkPCLConversions::PointCloudFromPolyData(input, inputCloud);

  pcl::PassThrough<PointType> filter;
  filter.setInputCloud(inputCloud);
  filter.setFilterFieldName(this->FieldName);
  filter.setFilterLimits(this->Limits[0], this->Limits[1]);
  filter.setFilterLimitsNegative(this->Invert);
  filter.filter(* outputCloud);
  
  // pcl::io::pointCloudTovtkPolyData(outputCloud, output);
  vtkPCLConversions::PolyDataFromPointCloud(outputCloud, output);
}

