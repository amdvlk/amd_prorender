/*****************************************************************************\
*
*  Module Name    rprMaterialXML.h
*  Project        AMD Radeon ProRender
*
*  Description    Radeon ProRender Interface header
*
*  Copyright(C) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
*
\*****************************************************************************/

#include "RadeonProRender.h"

#include <string>
#include <vector>
#include <unordered_map>

struct RPR_TOOL_NODE_MATERIAL_IMPORTED
{
	RPR_TOOL_NODE_MATERIAL_IMPORTED()
	{
		matNode = 0;
		materialType = (rpr_material_node_type)0;
		image = 0;
		light = 0;
		imageGamma = 1.0f;
		tilingX = 1.0;
		tilingY = 1.0;
	}

	std::string nodeName; // example "box0"
	rpr_material_node matNode;
	rpr_material_node_type materialType;   // example : RPR_MATERIAL_NODE_INPUT_LOOKUP
	rpr_image image;
	rpr_light light;
	float imageGamma; // only used if image != null
	std::string imagePath; // only used if image != null

	float tilingX;
	float tilingY;

	std::vector<  std::pair< std::string , std::pair<std::string,rpr_material_node_input> > > connecNode_; // list of connection to this node
};

// EXPORT a material and all its children materials tree into an XML file.
// 
// [input] masterMaterial : material to export
// [input] masterMaterial_displacement : optional, can be nullptr.  - displacement material associated with the base material
// [input] xmlFilePath : name of the XML file to generate
//
// [input] materialName : material name 
//
// Note that this exporter does not manage export of image data: it assumes all images are already on HDD and that paths are stored within rprObjectSetName().
// So make sure rpr_image names are correct before calling rprtools_MaterialXMLExport.
//
// returns RPR_SUCCESS if success.
//
rpr_int rprtools_MaterialXMLExport(
	rpr_material_node masterMaterial, 
	rpr_material_node masterMaterial_displacement, 
	const char* xmlFilePath,
	const char* materialName
);

//IMPORT and CREATE a material ( and all its children materials tree ) from an XML file.
//
// [input] context : the RPR context
// [input] matSystem : the material system of the context
// [input] imageBaseFolderPath : folder containing all the images listed in the XML file. example : "data/matlib/"
// [input] xmlFilePath : path to the XML file
//
// [output] masterMaterialIndex index in matNodeList of the master material ( father of all other material nodes )
// [output] matNodeList : list generated by this function.  list of all nodes stored in the XML.
// [output] masterMaterialIndex_displacement index in matNodeList of the displacement material ( -1 if no displacement material )
// [output] sometimes, the XML can generate some extra rpr_material_node materials. they will be listed in this output.
//
// returns RPR_SUCCESS if success.
//
rpr_int rprtools_MaterialXMLImport(
	rpr_context context, 
	rpr_material_system matSystem, 
	const char* imageBaseFolderPath,
	const char* xmlFilePath,
	int& masterMaterialIndex, // 
	std::vector<RPR_TOOL_NODE_MATERIAL_IMPORTED>& matNodeList,
	int& masterMaterialIndex_displacement, 
	std::vector<rpr_material_node>& extraArithmeticNodes
	);

