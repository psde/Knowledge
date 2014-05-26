# Wtf ...
function(FindQt5Module module)
	if(DEFINED Qt_ROOT)
		set("Qt5${module}_DIR" "${Qt_ROOT}/qtbase/lib/cmake/Qt5${module}")
		set("Qt5${module}_DIR" "${Qt5${module}_DIR}" PARENT_SCOPE)
	endif()

	find_package("Qt5${module}" 5.2 REQUIRED)
	message(STATUS "Found Qt5${module} config in ${Qt5${module}_DIR}")
endfunction()
