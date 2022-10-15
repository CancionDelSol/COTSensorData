cmake_minimum_required(VERSION 3.19)

if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(SandboxLegacy LANGUAGES MikroC)
else()
    project(SandboxLegacy LANGUAGES C ASM)
endif()

set(PROJECT_TYPE "legacy" CACHE STRING "" FORCE)

add_executable(SandboxLegacy
main.c
mac_ca821x.h
ca821x_spi.h
ca821x_irq.h
ca821x_bsp.h
mac_messages.h
ieee_802_15_4.h
hwme_tdme.h
ca821x_api.h
log.h
ca821x_spi.c
ca821x_irq.c
ca821x_bsp.c
ca821x_api.c
mac_ca821x.c
)

############################ SandboxLegacy GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(SandboxLegacy PUBLIC MikroC.Core)
find_package(MikroC.UART REQUIRED)
target_link_libraries(SandboxLegacy PUBLIC MikroC.UART)
find_package(MikroC.System REQUIRED)
target_link_libraries(SandboxLegacy PUBLIC MikroC.System)
find_package(MikroC.SPI REQUIRED)
target_link_libraries(SandboxLegacy PUBLIC MikroC.SPI)
find_package(MikroC.Peripheral_Pin_Select REQUIRED)
target_link_libraries(SandboxLegacy PUBLIC MikroC.Peripheral_Pin_Select)
find_package(MikroC.C_Type REQUIRED)
target_link_libraries(SandboxLegacy PUBLIC MikroC.C_Type)
find_package(MikroC.C_String REQUIRED)
target_link_libraries(SandboxLegacy PUBLIC MikroC.C_String)
find_package(MikroC.C_Stdlib REQUIRED)
target_link_libraries(SandboxLegacy PUBLIC MikroC.C_Stdlib)
find_package(MikroC.Conversions REQUIRED)
target_link_libraries(SandboxLegacy PUBLIC MikroC.Conversions)
find_package(MikroC.C_Math REQUIRED)
target_link_libraries(SandboxLegacy PUBLIC MikroC.C_Math)
find_package(MikroC.Button REQUIRED)
target_link_libraries(SandboxLegacy PUBLIC MikroC.Button)
############################ SandboxLegacy GENERATED CODE END ###########################
if (${MIKROSDK_TYPE} STREQUAL "mikrosdk")
    find_package(MikroC.Core REQUIRED)
    target_link_libraries(SandboxLegacy
        PUBLIC
            MikroC.Core
    )
else()
    find_package(MikroC.System REQUIRED)
    target_link_libraries(SandboxLegacy
        PUBLIC
            MikroC.System
    )
endif()
