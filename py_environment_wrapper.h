/**
 * @file: py_environment_wrapper.h
 * 
 * @author: Marck Herzon Barrion - <herzon.barrion@gmail.com>
 * 
 * An extension of the work of Ken Hasselmann (https://github.com/KenN7/argos-python)
 * 
 * Based on the crazyflie ARGoS model of Daniel H. Stolfi and Gregoire Danoy (https://arxiv.org/abs/2401.16948)
 * 
 * Using the ARGoS Simulator created by Carlo Pinciroli (https://github.com/ilpincy/argos3)
 */

#ifndef PY_ENVIRONMENT_WRAPPER_H
#define PY_ENVIRONMENT_WRAPPER_H

#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/core/utility/math/general.h>
#include <iostream>
#include <string>

namespace argos {

	class CQTOpenGLUserFunctionsWrapper {
	  public:
	    CQTOpenGLUserFunctionsWrapper();
	    ~CQTOpenGLUserFunctionsWrapper(){};

	    argos::CQTOpenGLUserFunctions* m_pcCQTOpenGLUserFunctions;

	    void SetDrawList(const std::string& key, const std::string& value);

	    const std::string GetDrawList(const std::string& key);

	    std::map<std::string, std::string> m_cAttributes;

	    void DrawCircle(
	      const boost::python::list c_position_list, 
	      const boost::python::list c_orientation_list, 
	      const Real f_radius, 
	      const boost::python::object color_str_list,
	      const bool  b_fill=true);

	    void DrawPolygon(
	      const boost::python::list c_position_list, 
	      const boost::python::list c_orientation_list, 
	      const boost::python::list vec_points, 
	      const std::string str_color_name,
	      const bool  b_fill);
	    
	    void DrawRay(
	      const boost::python::list c_start,
	      const boost::python::list c_end,
	      const boost::python::object str_color_name,
	      const Real f_width);

	    void DrawCylinder(
	      const boost::python::list c_position_list, 
	      const boost::python::list c_orientation_list, 
	      const Real f_radius,
	      const Real f_height,  
	      const std::string str_color_name);

	    void DrawBox(
	      const boost::python::list c_position_list, 
	      const boost::python::list c_orientation_list, 
	      const boost::python::list c_size_list, 
	      const boost::python::object str_color_name);

	    void DrawText(
	      const boost::python::list c_position,
	      const std::string str_text,
	      const std::string str_color_name); 

	    void CloseWindow();
	};
};

#endif
