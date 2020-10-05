#ifndef _OCM_TF_OPS_LIST_H_
#define _OCM_TF_OPS_LIST_H_

#include <iostream>
#include <set>

namespace ocm{

//OpenVINO 2021.1 supported TF ops
std::set<std::string> common_supported_ops = {
	"Add",
	"AddN",
	"AddV2",  // implemented using ngraph ADD
	"ArgMax",
	"AvgPool",
	"BiasAdd",
	"ConcatV2",
	"Const",
	"Conv2D",
	"Fill",   // implemented using broadcast
	"FusedBatchNorm",
	"Identity",
	"MatMul",
	"MaxPool",
	"Mean",
	"Mul",
	"Pack",
	"Pad",
	"Placeholder",
	"Relu",
	"Reshape",
	"Shape",
	"Softmax",
	"Squeeze",
	"StridedSlice",
	"Sub",
};

//TF OPs supported through composite ops i.e. translated using multiple other available Ngaph OPs
std::set<std::string> composite_ops = {
	"FusedBatchNormV3",
	"_FusedConv2D",
	"_FusedMatMul",
};

//Op supported only on CPU and not supported on VPU
std::set<std::string> cpu_only_ops = {
};

std::set<std::string> gpu_only_ops = {
};

std::set<std::string> vpu_only_ops = {
};

} //namespace ocm 

#endif //_OCM_TF_OPS_LIST_H_