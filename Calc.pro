TEMPLATE  = subdirs
CONFIG   += ordered

SUBDIRS += \
    src/Lib/daq_ipc_lib \        # библиотека для межпроцессного взаимодействия
    src/Lib/daq_plugins \        # плагины
    src/Lib/db/daq_libpq \       # библиотека подключения к БД PostgreSQL
    src/Lib/lib_cms \            # библиотека формирования параметров станции
    src/Lib/daq_parsers \        # библиотека с парсингами устройств
    src/App/arm_scheme \         # основное приложение схемы
    src/App/plugins_loader \     # приложение для запуска плагинов
    src/App/plugins_loader_gui \ # приложение для запуска плагинов
    utils/monitor \
