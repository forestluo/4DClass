///////////////////////////////////////////////////////////////////////////////
//
// 4DProperties.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _4D_PROPERTIES_H_
#define _4D_PROPERTIES_H_

///////////////////////////////////////////////////////////////////////////////
//
// Definitions
//
///////////////////////////////////////////////////////////////////////////////

#define PROPERTY_GENERAL									_T("常规属性")
#define PROPERTY_GENERAL_SELECTION							0

#define PROPERTY_FENCE										_T("干涉检测")
#define PROPERTY_FENCE_SELECTION							1

#define PROPERTY_RENDER										_T("几何绘制")
#define PROPERTY_RENDER_SELECTION							2

#define PROPERTY_PHYSICS									_T("物理属性")
#define PROPERTY_PHYSICS_SELECTION							3

#define PROPERTY_PHYSICS_FORCE								_T("力学参数")
#define PROPERTY_PHYSICS_FORCE_SELECTION					4

#define PROPERTY_JOINT										_T("铰链属性")
#define PROPERTY_JOINT_SELECTION							5

#define PROPERTY_JOINT_FORCE								_T("铰链参数")
#define PROPERTY_JOINT_FORCE_SELECTION						6

#define HANDLE_GROUP_MAJOR									(g_pPropHandles[0])
#define HANDLE_NAME											(g_pPropHandles[1])
#define HANDLE_TYPE											(g_pPropHandles[2])
#define HANDLE_FILE_NAME									(g_pPropHandles[3])
#define HANDLE_SOURCE_NAME									(g_pPropHandles[3])
#define HANDLE_REFERENCED_COUNT								(g_pPropHandles[4])

#define HANDLE_GROUP_MISC									(g_pPropHandles[5])
#define HANDLE_GLOBAL_COLOR									(g_pPropHandles[6])

#define HANDLE_GROUP_PARAMETER								(g_pPropHandles[7])

#define HANDLE_TEXTURE_DIMENSION							(g_pPropHandles[8])
#define HANDLE_TEXTURE_DIMENSION_WIDTH						(g_pPropHandles[9])
#define HANDLE_TEXTURE_DIMENSION_HEIGHT						(g_pPropHandles[10])

#define HANDLE_PSEYE_FPS									(g_pPropHandles[8])
#define HANDLE_PSEYE_COLOR_MODE								(g_pPropHandles[9])
#define HANDLE_PSEYE_RESOLUTION								(g_pPropHandles[10])
#define HANDLE_PSEYE_SENSOR									(g_pPropHandles[11])
#define HANDLE_PSEYE_SENSOR_GAIN							(g_pPropHandles[12])
#define HANDLE_PSEYE_SENSOR_EXPOSURE						(g_pPropHandles[13])
#define HANDLE_PSEYE_SENSOR_AUTOGAIN						(g_pPropHandles[14])
#define HANDLE_PSEYE_SENSOR_AUTOEXPOSURE					(g_pPropHandles[15])
#define HANDLE_PSEYE_SENSOR_AUTOWHITEBALANCE				(g_pPropHandles[16])
#define HANDLE_PSEYE_LINEAR									(g_pPropHandles[17])
#define HANDLE_PSEYE_LINEAR_ZOOM							(g_pPropHandles[18])
#define HANDLE_PSEYE_LINEAR_ROTATION						(g_pPropHandles[19])
#define HANDLE_PSEYE_LINEAR_HFLIP							(g_pPropHandles[20])
#define HANDLE_PSEYE_LINEAR_VFLIP							(g_pPropHandles[21])
#define HANDLE_PSEYE_LINEAR_XOFFSET							(g_pPropHandles[22])
#define HANDLE_PSEYE_LINEAR_YOFFSET							(g_pPropHandles[23])
#define HANDLE_PSEYE_LINEAR_HKEYSTONE						(g_pPropHandles[24])
#define HANDLE_PSEYE_LINEAR_VKEYSTONE						(g_pPropHandles[25])
#define HANDLE_PSEYE_NONELINEAR								(g_pPropHandles[26])
#define HANDLE_PSEYE_NONELINEAR_LENSBRIGHTNESS				(g_pPropHandles[27])
#define HANDLE_PSEYE_NONELINEAR_LENSCORRECTION1				(g_pPropHandles[28])
#define HANDLE_PSEYE_NONELINEAR_LENSCORRECTION2				(g_pPropHandles[29])
#define HANDLE_PSEYE_NONELINEAR_LENSCORRECTION3				(g_pPropHandles[30])

#define HANDLE_HAAR_DEVICE									(g_pPropHandles[8])
#define HANDLE_HAAR_DETECTING								(g_pPropHandles[9])
#define HANDLE_HAAR_TRACKING								(g_pPropHandles[10])
#define HANDLE_HAAR_FACE									(g_pPropHandles[11])
#define HANDLE_HAAR_FACE_CENTER								(g_pPropHandles[12])
#define HANDLE_HAAR_FACE_CENTER_X							(g_pPropHandles[13])
#define HANDLE_HAAR_FACE_CENTER_Y							(g_pPropHandles[14])
#define HANDLE_HAAR_BALL									(g_pPropHandles[15])
#define HANDLE_HAAR_BALL_ROTATION							(g_pPropHandles[16])
#define HANDLE_HAAR_BALL_ROTATION_X							(g_pPropHandles[17])
#define HANDLE_HAAR_BALL_ROTATION_Y							(g_pPropHandles[18])
#define HANDLE_HAAR_BALL_ROTATION_Z							(g_pPropHandles[19])

#define HANDLE_GROUP_MATRIX									(g_pPropHandles[8])
#define HANDLE_MATRIX_WORLD									(g_pPropHandles[9])
#define HANDLE_MATRIX_VIEW									(g_pPropHandles[10])
#define HANDLE_MATRIX_PROJECTION							(g_pPropHandles[11])
#define HANDLE_MATRIX_VIEW_INVERSE							(g_pPropHandles[12])
#define HANDLE_MATRIX_VIEW_PROJECTION						(g_pPropHandles[13])

#define HANDLE_GROUP_MATERIAL								(g_pPropHandles[14])
#define HANDLE_MATERIAL_POWER								(g_pPropHandles[15])
#define HANDLE_MATERIAL_DIFFUSE								(g_pPropHandles[16])
#define HANDLE_MATERIAL_SPECULAR							(g_pPropHandles[17])
#define HANDLE_MATERIAL_AMBIENT								(g_pPropHandles[18])
#define HANDLE_MATERIAL_EMISSIVE							(g_pPropHandles[19])
#define HANDLE_MATERIAL_TEXTURE								(g_pPropHandles[20])

#define HANDLE_GROUP_TEXTURE								(g_pPropHandles[21])
#define HANDLE_TEXTURE_SCENE								(g_pPropHandles[22])
#define HANDLE_TEXTURE_ENVIRONMENT							(g_pPropHandles[23])

#define HANDLE_MESH_BASIC									(g_pPropHandles[8])
#define HANDLE_MESH_BASIC_VERTEX_COUNT						(g_pPropHandles[9])
#define HANDLE_MESH_BASIC_TRIANGLE_COUNT					(g_pPropHandles[10])
#define HANDLE_MESH_BASIC_VERTEX_SIZE						(g_pPropHandles[11])

#define HANDLE_MESH_MATERIAL								(g_pPropHandles[12])
#define HANDLE_MESH_MATERIAL_ENABLED						(g_pPropHandles[13])
#define HANDLE_MESH_MATERIAL_COUNT							(g_pPropHandles[14])

#define HANDLE_PRIMITIVE_BASIC								(g_pPropHandles[8])
#define HANDLE_PRIMITIVE_BASIC_INDEX_COUNT					(g_pPropHandles[9])
#define HANDLE_PRIMITIVE_BASIC_RING_COUNT					(g_pPropHandles[10])
#define HANDLE_PRIMITIVE_BASIC_VERTEX_COUNT					(g_pPropHandles[11])
#define HANDLE_PRIMITIVE_BASIC_SEGMENT_COUNT				(g_pPropHandles[12])
#define HANDLE_PRIMITIVE_BASIC_VERTEX_SIZE					(g_pPropHandles[13])

#define HANDLE_PRIMITIVE_GEOMETRY							(g_pPropHandles[14])
#define HANDLE_PRIMITIVE_GEOMETRY_TYPE						(g_pPropHandles[15])

#define HANDLE_PRIMITIVE_GEOMETRY_WIDTH						(g_pPropHandles[16])
#define HANDLE_PRIMITIVE_GEOMETRY_HEIGHT					(g_pPropHandles[17])
#define HANDLE_PRIMITIVE_GEOMETRY_DEPTH						(g_pPropHandles[18])
#define HANDLE_PRIMITIVE_GEOMETRY_RADIUS					(g_pPropHandles[19])
#define HANDLE_PRIMITIVE_GEOMETRY_RADIUS1					(g_pPropHandles[20])
#define HANDLE_PRIMITIVE_GEOMETRY_RADIUS2					(g_pPropHandles[21])

#define HANDLE_PRIMITIVE_GEOMETRY_VERTEX1					(g_pPropHandles[16])
#define HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_X					(g_pPropHandles[17])
#define HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_Y					(g_pPropHandles[18])
#define HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_Z					(g_pPropHandles[19])

#define HANDLE_PRIMITIVE_GEOMETRY_VERTEX2					(g_pPropHandles[20])
#define HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_X					(g_pPropHandles[21])
#define HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_Y					(g_pPropHandles[22])
#define HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_Z					(g_pPropHandles[23])

#define HANDLE_PRIMITIVE_GEOMETRY_VERTEX3					(g_pPropHandles[24])
#define HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_X					(g_pPropHandles[25])
#define HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_Y					(g_pPropHandles[25])
#define HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_Z					(g_pPropHandles[27])

#define HANDLE_PRIMITIVE_GEOMETRY_VERTEX4					(g_pPropHandles[28])
#define HANDLE_PRIMITIVE_GEOMETRY_VERTEX4_X					(g_pPropHandles[29])
#define HANDLE_PRIMITIVE_GEOMETRY_VERTEX4_Y					(g_pPropHandles[30])
#define HANDLE_PRIMITIVE_GEOMETRY_VERTEX4_Z					(g_pPropHandles[31])

//Box General Page
#define HANDLE_GROUP_BOX									(g_pPropHandles[8])
#define HANDLE_BOX_BALL										(g_pPropHandles[9])
#define HANDLE_BOX_BALL_CENTER								(g_pPropHandles[10])
#define HANDLE_BOX_BALL_CENTER_X							(g_pPropHandles[11])
#define HANDLE_BOX_BALL_CENTER_Y							(g_pPropHandles[12])
#define HANDLE_BOX_BALL_CENTER_Z							(g_pPropHandles[13])
#define HANDLE_BOX_BALL_EXTEND								(g_pPropHandles[14])
#define HANDLE_BOX_BALL_EXTEND_R							(g_pPropHandles[15])

#define HANDLE_BOX_AABOX									(g_pPropHandles[16])
#define HANDLE_BOX_AABOX_CENTER								(g_pPropHandles[17])
#define HANDLE_BOX_AABOX_CENTER_X							(g_pPropHandles[18])
#define HANDLE_BOX_AABOX_CENTER_Y							(g_pPropHandles[19])
#define HANDLE_BOX_AABOX_CENTER_Z							(g_pPropHandles[20])
#define HANDLE_BOX_AABOX_EXTEND								(g_pPropHandles[21])
#define HANDLE_BOX_AABOX_EXTEND_X							(g_pPropHandles[22])
#define HANDLE_BOX_AABOX_EXTEND_Y							(g_pPropHandles[23])
#define HANDLE_BOX_AABOX_EXTEND_Z							(g_pPropHandles[24])

//Viewport General Page
#define HANDLE_GROUP_CAMERA									(g_pPropHandles[8])
#define HANDLE_GROUP_CAMERA_POSITION						(g_pPropHandles[9])
#define HANDLE_GROUP_CAMERA_POSITION_X						(g_pPropHandles[10])
#define HANDLE_GROUP_CAMERA_POSITION_Y						(g_pPropHandles[11])
#define HANDLE_GROUP_CAMERA_POSITION_Z						(g_pPropHandles[12])
#define HANDLE_GROUP_CAMERA_LOOKAT							(g_pPropHandles[13])
#define HANDLE_GROUP_CAMERA_LOOKAT_X						(g_pPropHandles[14])
#define HANDLE_GROUP_CAMERA_LOOKAT_Y						(g_pPropHandles[15])
#define HANDLE_GROUP_CAMERA_LOOKAT_Z						(g_pPropHandles[16])
#define HANDLE_GROUP_CAMERA_PROJECTION						(g_pPropHandles[17])
#define HANDLE_GROUP_CAMERA_PROJECTION_FOV					(g_pPropHandles[18])
#define HANDLE_GROUP_CAMERA_PROJECTION_ASPECT				(g_pPropHandles[19])
#define HANDLE_GROUP_CAMERA_PROJECTION_ZFAR					(g_pPropHandles[20])
#define HANDLE_GROUP_CAMERA_PROJECTION_ZNEAR				(g_pPropHandles[21])

#define HANDLE_GROUP_MOUSE									(g_pPropHandles[22])
#define HANDLE_GROUP_MOUSE_SCREEN_X							(g_pPropHandles[23])
#define HANDLE_GROUP_MOUSE_SCREEN_Y							(g_pPropHandles[24])

//Object General Page
#define HANDLE_OBJECT_TRANSFORM								(g_pPropHandles[8])
#define HANDLE_OBJECT_TRANSFORM_SCALE						(g_pPropHandles[9])
#define HANDLE_OBJECT_TRANSFORM_SCALE_X						(g_pPropHandles[10])
#define HANDLE_OBJECT_TRANSFORM_SCALE_Y						(g_pPropHandles[11])
#define HANDLE_OBJECT_TRANSFORM_SCALE_Z						(g_pPropHandles[12])
#define HANDLE_OBJECT_TRANSFORM_ROTATE						(g_pPropHandles[13])
#define HANDLE_OBJECT_TRANSFORM_ROTATE_X					(g_pPropHandles[14])
#define HANDLE_OBJECT_TRANSFORM_ROTATE_Y					(g_pPropHandles[15])
#define HANDLE_OBJECT_TRANSFORM_ROTATE_Z					(g_pPropHandles[16])
#define HANDLE_OBJECT_TRANSFORM_TRANSLATE					(g_pPropHandles[17])
#define HANDLE_OBJECT_TRANSFORM_TRANSLATE_X					(g_pPropHandles[18])
#define HANDLE_OBJECT_TRANSFORM_TRANSLATE_Y					(g_pPropHandles[19])
#define HANDLE_OBJECT_TRANSFORM_TRANSLATE_Z					(g_pPropHandles[20])
#define HANDLE_OBJECT_CONTROL								(g_pPropHandles[21])
#define HANDLE_OBJECT_CONTROL_SCALABLE						(g_pPropHandles[22])
#define HANDLE_OBJECT_CONTROL_MOVABLE						(g_pPropHandles[23])
#define HANDLE_OBJECT_CONTROL_ROTATABLE						(g_pPropHandles[24])
#define HANDLE_OBJECT_MISC_PICKED							(g_pPropHandles[25])

//Render General Page
#define HANDLE_RENDER_MODEL_NAME							(g_pPropHandles[8])
#define HANDLE_RENDER_EFFECT_NAME							(g_pPropHandles[9])
#define HANDLE_RENDER_COLOR									(g_pPropHandles[10])
#define HANDLE_RENDER_COLOR_GLOBAL							(g_pPropHandles[11])
#define HANDLE_RENDER_LIGHT									(g_pPropHandles[12])
#define HANDLE_RENDER_LIGHT_COLOR							(g_pPropHandles[13])
#define HANDLE_RENDER_TEXTURE								(g_pPropHandles[14])
#define HANDLE_RENDER_TEXTURE_SCENE							(g_pPropHandles[15])
#define HANDLE_RENDER_TEXTURE_ENVIRONMENT					(g_pPropHandles[16])

#define HANDLE_RENDER_DEBUG									(g_pPropHandles[17])
#define HANDLE_RENDER_DEBUG_LOCAL_AXIS						(g_pPropHandles[18])
#define HANDLE_RENDER_DEBUG_BOX								(g_pPropHandles[19])
#define HANDLE_RENDER_DEBUG_BOX_AABOX						(g_pPropHandles[20])
#define HANDLE_RENDER_DEBUG_BOX_SPHERE						(g_pPropHandles[21])
#define HANDLE_RENDER_DEBUG_JOINT							(g_pPropHandles[22])
#define HANDLE_RENDER_DEBUG_JOINT_SPHERE					(g_pPropHandles[23])
#define HANDLE_RENDER_DEBUG_JOINT_POSITION					(g_pPropHandles[24])
#define HANDLE_RENDER_DEBUG_JOINT_DIRECTION					(g_pPropHandles[25])

//Physics General Page
#define HANDLE_PHYSICS_GENERAL								(g_pPropHandles[8])
#define HANDLE_PHYSICS_GENERAL_MASS							(g_pPropHandles[9])
#define HANDLE_PHYSICS_GENERAL_VOLUMN						(g_pPropHandles[10])
#define HANDLE_PHYSICS_GENERAL_DENSITY						(g_pPropHandles[11])

#define HANDLE_PHYSICS_GENERAL_INERTIA						(g_pPropHandles[12])
#define HANDLE_PHYSICS_GENERAL_INERTIA_IXX					(g_pPropHandles[13])
#define HANDLE_PHYSICS_GENERAL_INERTIA_IYY					(g_pPropHandles[14])
#define HANDLE_PHYSICS_GENERAL_INERTIA_IZZ					(g_pPropHandles[15])

//Physics Force Page
#define HANDLE_PHYSICS_FORCE								(g_pPropHandles[8])
#define HANDLE_PHYSICS_FORCE_X								(g_pPropHandles[9])
#define HANDLE_PHYSICS_FORCE_Y								(g_pPropHandles[10])
#define HANDLE_PHYSICS_FORCE_Z								(g_pPropHandles[11])

#define HANDLE_PHYSICS_TORQUE								(g_pPropHandles[12])
#define HANDLE_PHYSICS_TORQUE_X								(g_pPropHandles[13])
#define HANDLE_PHYSICS_TORQUE_Y								(g_pPropHandles[14])
#define HANDLE_PHYSICS_TORQUE_Z								(g_pPropHandles[15])

#define HANDLE_PHYSICS_VELOCITY								(g_pPropHandles[16])
#define HANDLE_PHYSICS_VELOCITY_X							(g_pPropHandles[17])
#define HANDLE_PHYSICS_VELOCITY_Y							(g_pPropHandles[18])
#define HANDLE_PHYSICS_VELOCITY_Z							(g_pPropHandles[19])

#define HANDLE_PHYSICS_OMEGA								(g_pPropHandles[20])
#define HANDLE_PHYSICS_OMEGA_X								(g_pPropHandles[21])
#define HANDLE_PHYSICS_OMEGA_Y								(g_pPropHandles[22])
#define HANDLE_PHYSICS_OMEGA_Z								(g_pPropHandles[23])

#define HANDLE_PHYSICS_ACCELERATION							(g_pPropHandles[24])
#define HANDLE_PHYSICS_ACCELERATION_X						(g_pPropHandles[25])
#define HANDLE_PHYSICS_ACCELERATION_Y						(g_pPropHandles[26])
#define HANDLE_PHYSICS_ACCELERATION_Z						(g_pPropHandles[27])

#define HANDLE_PHYSICS_ALPHA								(g_pPropHandles[28])
#define HANDLE_PHYSICS_ALPHA_X								(g_pPropHandles[29])
#define HANDLE_PHYSICS_ALPHA_Y								(g_pPropHandles[30])
#define HANDLE_PHYSICS_ALPHA_Z								(g_pPropHandles[31])

//Joint Force General Page
#define HANDLE_JOINT_TYPE									(g_pPropHandles[8])
#define HANDLE_JOINT_CHILD_NAME								(g_pPropHandles[9])
#define HANDLE_JOINT_PARENT_NAME							(g_pPropHandles[10])
#define HANDLE_JOINT_STIFFNESS								(g_pPropHandles[11])
#define HANDLE_JOINT_SELF_COLLISION							(g_pPropHandles[12])

#define HANDLE_JOINT_BALL_LIMIT								(g_pPropHandles[13])
#define HANDLE_JOINT_BALL_LIMIT_MAX_CONE_ANGLE				(g_pPropHandles[14])
#define HANDLE_JOINT_BALL_LIMIT_MAX_TWIST_ANGLE				(g_pPropHandles[15])
#define HANDLE_JOINT_BALL_LIMIT_MIN_TWIST_ANGLE				(g_pPropHandles[16])
#define HANDLE_JOINT_BALL_LIMIT_CONE_AXIS					(g_pPropHandles[17])
#define HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_X					(g_pPropHandles[18])
#define HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_Y					(g_pPropHandles[19])
#define HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_Z					(g_pPropHandles[20])

#define HANDLE_JOINT_HINGE_LIMIT							(g_pPropHandles[13])
#define HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS					(g_pPropHandles[16])
#define HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_X				(g_pPropHandles[17])
#define HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Y				(g_pPropHandles[18])
#define HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Z				(g_pPropHandles[19])

#define HANDLE_JOINT_SLIDER_LIMIT							(g_pPropHandles[13])
#define HANDLE_JOINT_SLIDER_LIMIT_DIRECTION					(g_pPropHandles[16])
#define HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_X				(g_pPropHandles[17])
#define HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Y				(g_pPropHandles[18])
#define HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Z				(g_pPropHandles[19])

#define HANDLE_JOINT_CORKSCREW_LIMIT						(g_pPropHandles[13])
#define HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION				(g_pPropHandles[16])
#define HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION_X			(g_pPropHandles[17])
#define HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION_Y			(g_pPropHandles[18])
#define HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION_Z			(g_pPropHandles[19])

#define HANDLE_JOINT_UNIVERSAL_LIMIT						(g_pPropHandles[13])
#define HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0				(g_pPropHandles[16])
#define HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_X			(g_pPropHandles[17])
#define HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_Y			(g_pPropHandles[18])
#define HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_Z			(g_pPropHandles[19])
#define HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1				(g_pPropHandles[20])
#define HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_X			(g_pPropHandles[21])
#define HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_Y			(g_pPropHandles[22])
#define HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_Z			(g_pPropHandles[23])

#define HANDLE_JOINT_UPVECTOR_LIMIT							(g_pPropHandles[13])
#define HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION				(g_pPropHandles[16])
#define HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_X				(g_pPropHandles[17])
#define HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_Y				(g_pPropHandles[18])
#define HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_Z				(g_pPropHandles[19])

#define HANDLE_JOINT_LINEAR_LIMIT							(g_pPropHandles[13])
#define HANDLE_JOINT_LINEAR_LIMIT_MIN						(g_pPropHandles[14])
#define HANDLE_JOINT_LINEAR_LIMIT_MIN_X						(g_pPropHandles[15])
#define HANDLE_JOINT_LINEAR_LIMIT_MIN_Y						(g_pPropHandles[16])
#define HANDLE_JOINT_LINEAR_LIMIT_MIN_Z						(g_pPropHandles[17])
#define HANDLE_JOINT_LINEAR_LIMIT_MAX						(g_pPropHandles[18])
#define HANDLE_JOINT_LINEAR_LIMIT_MAX_X						(g_pPropHandles[19])
#define HANDLE_JOINT_LINEAR_LIMIT_MAX_Y						(g_pPropHandles[20])
#define HANDLE_JOINT_LINEAR_LIMIT_MAX_Z						(g_pPropHandles[21])

#define HANDLE_JOINT_ANGULA_LIMIT							(g_pPropHandles[22])
#define HANDLE_JOINT_ANGULA_LIMIT_MIN						(g_pPropHandles[23])
#define HANDLE_JOINT_ANGULA_LIMIT_MIN_X						(g_pPropHandles[24])
#define HANDLE_JOINT_ANGULA_LIMIT_MIN_Y						(g_pPropHandles[25])
#define HANDLE_JOINT_ANGULA_LIMIT_MIN_Z						(g_pPropHandles[26])
#define HANDLE_JOINT_ANGULA_LIMIT_MAX						(g_pPropHandles[27])
#define HANDLE_JOINT_ANGULA_LIMIT_MAX_X						(g_pPropHandles[28])
#define HANDLE_JOINT_ANGULA_LIMIT_MAX_Y						(g_pPropHandles[29])
#define HANDLE_JOINT_ANGULA_LIMIT_MAX_Z						(g_pPropHandles[30])

#define HANDLE_JOINT_DIRECTION								(g_pPropHandles[31])
#define HANDLE_JOINT_MAJOR_DIRECTION						(g_pPropHandles[32])
#define HANDLE_JOINT_MAJOR_DIRECTION_X						(g_pPropHandles[33])
#define HANDLE_JOINT_MAJOR_DIRECTION_Y						(g_pPropHandles[34])
#define HANDLE_JOINT_MAJOR_DIRECTION_Z						(g_pPropHandles[35])
#define HANDLE_JOINT_MINOR_DIRECTION						(g_pPropHandles[36])
#define HANDLE_JOINT_MINOR_DIRECTION_X						(g_pPropHandles[37])
#define HANDLE_JOINT_MINOR_DIRECTION_Y						(g_pPropHandles[38])
#define HANDLE_JOINT_MINOR_DIRECTION_Z						(g_pPropHandles[39])

//Joint Force Page
#define HANDLE_PHYSICS_JOINT_FORCE							(g_pPropHandles[8])
#define HANDLE_PHYSICS_JOINT_FORCE_X						(g_pPropHandles[9])
#define HANDLE_PHYSICS_JOINT_FORCE_Y						(g_pPropHandles[10])
#define HANDLE_PHYSICS_JOINT_FORCE_Z						(g_pPropHandles[11])

#define HANDLE_PHYSICS_JOINT_OMEGA							(g_pPropHandles[12])
#define HANDLE_PHYSICS_JOINT_OMEGA_X						(g_pPropHandles[13])
#define HANDLE_PHYSICS_JOINT_OMEGA_Y						(g_pPropHandles[14])
#define HANDLE_PHYSICS_JOINT_OMEGA_Z						(g_pPropHandles[15])

#define HANDLE_PHYSICS_JOINT_ANGLE							(g_pPropHandles[16])
#define HANDLE_PHYSICS_JOINT_ANGLE_X						(g_pPropHandles[17])
#define HANDLE_PHYSICS_JOINT_ANGLE_Y						(g_pPropHandles[18])
#define HANDLE_PHYSICS_JOINT_ANGLE_Z						(g_pPropHandles[19])

#define HANDLE_PHYSICS_JOINT_POSITION						(g_pPropHandles[20])
#define HANDLE_PHYSICS_JOINT_POSITION_X						(g_pPropHandles[21])
#define HANDLE_PHYSICS_JOINT_POSITION_Y						(g_pPropHandles[22])
#define HANDLE_PHYSICS_JOINT_POSITION_Z						(g_pPropHandles[23])

#define HANDLE_PHYSICS_JOINT_VELOCITY						(g_pPropHandles[24])
#define HANDLE_PHYSICS_JOINT_VELOCITY_X						(g_pPropHandles[25])
#define HANDLE_PHYSICS_JOINT_VELOCITY_Y						(g_pPropHandles[26])
#define HANDLE_PHYSICS_JOINT_VELOCITY_Z						(g_pPropHandles[27])

///////////////////////////////////////////////////////////////////////////////
//
// Definitions
//
///////////////////////////////////////////////////////////////////////////////

#define _FORMAT_FLOAT_										_T("±%f")

///////////////////////////////////////////////////////////////////////////////
#endif //_4D_PROPERTIES_H_