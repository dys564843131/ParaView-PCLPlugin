//==============================================================================
//
// Copyright 2012-2018 Kitware, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//==============================================================================

#include "vtkPCLWriter.h"

#include "vtkPolyData.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"

#include <pcl/point_types.h>

//------------------------------------------------------------------------------
vtkPCLWriter::vtkPCLWriter()
{
  this->FileName = nullptr;
}

//------------------------------------------------------------------------------
vtkPCLWriter::~vtkPCLWriter()
{
}

//------------------------------------------------------------------------------
void vtkPCLWriter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//------------------------------------------------------------------------------
void vtkPCLWriter::WriteData()
{
  vtkPolyData * input = vtkPolyData::SafeDownCast(this->GetInput(0));
  this->WritePCL(input);
}

//------------------------------------------------------------------------------
int vtkPCLWriter::FillInputPortInformation(int port, vtkInformation * info)
{
  if (port == 0)
  {
    info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkPolyData");
    return 1;
  }
  return 0;
}
