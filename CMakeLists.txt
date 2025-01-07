cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME "Filters")
set(FORMATS AU)

file(STRINGS VERSION CURRENT_VERSION)

project(${PROJECT_NAME} VERSION ${CURRENT_VERSION})

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Support macOS down to High Sierra")

# On by default as of CMAKE 3.26
#set_property(GLOBAL PROPERTY USE_FOLDERS YES)

# JUCE_ENABLE_MODULE_SOURCE_GROUPS
# This option will make module source files browsable in IDE projects.
# It has no effect in non-IDE projects. This option is off by default,
# as it will increase the size of generated IDE projects and might slow
# down configuration a bit. If you enable this, you should probably also
# add set_property(GLOBAL PROPERTY USE_FOLDERS YES) to your top level
# CMakeLists as this is required for source grouping to work.
#option(JUCE_ENABLE_MODULE_SOURCE_GROUPS "Show all module sources in IDE projects" ON)

add_subdirectory(JUCE)

juce_add_plugin(
    "${PROJECT_NAME}"
    COMPANY_NAME acanois
    BUNDLE_ID com.acanois.acanois
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Acan
    PLUGIN_CODE A001
    FORMATS "${FORMATS}"
    PRODUCT_NAME "${PROJECT_NAME}"
)

target_compile_features("${PROJECT_NAME}" PRIVATE cxx_std_20)

set(
    ProjectSource
    source/PluginEditor.h
    source/PluginProcessor.h
    source/HighPassFilter.h
    source/PluginEditor.cpp
    source/PluginProcessor.cpp
    source/HighPassFilter.cpp
)

target_sources("${PROJECT_NAME}" PRIVATE ${ProjectSource})
set_target_properties("${PROJECT_NAME}" PROPERTIES FOLDER "")

target_compile_definitions(
    "${PROJECT_NAME}"
    PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(
    "${PROJECT_NAME}"
    PUBLIC
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)
