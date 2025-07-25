include("C:/QtProjects/TextEditor/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/TextEditor-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE C:/QtProjects/TextEditor/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/TextEditor.exe
    GENERATE_QT_CONF
)
