# Wtf ...
function(FindQt5Module module)
	set("Qt5${module}_DIR" "${Qt_ROOT}/qtbase/lib/cmake/Qt5${module}")
	set("Qt5${module}_DIR" "${Qt_ROOT}/qtbase/lib/cmake/Qt5${module}" PARENT_SCOPE)
	find_package("Qt5${module}" REQUIRED)
	message(STATUS "Found Qt5${module} config in ${Qt5${module}_DIR}")
endfunction()