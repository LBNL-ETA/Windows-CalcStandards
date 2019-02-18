set( CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON )

add_library( ${LIB_NAME} 
		integration_rule.h
		create_integration_rule.h		
		create_integration_rule.cpp     
		load_standard.h
		load_standard.cpp
		create_spectrum.h               		
		create_spectrum.cpp             
		method.h
		method_text.h
		create_wavelength_boundary.h    
		create_wavelength_boundary.cpp  
		spectrum.h
		standard.h
		create_wavelength_set.h         
		create_wavelength_set.cpp       
		wavelength_boundary.h
		wavelength_set.h)



if(NOT "${fPIC}")
  set(fPIC ON)
endif()

if(fPIC)
  set_property(TARGET ${LIB_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

target_compile_options(${LIB_NAME} PRIVATE -Werror)
