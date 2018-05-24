
REGULAR_PWD=$(CURDIR)

SOURCES_DIR=${REGULAR_PWD}/../Sources
TIMESTAMPS=${REGULAR_PWD}/timestamps

DBUS_SRC_PATH=${REGULAR_PWD}/dbus-1.10.10
EXPAT_SRC_PATH=${REGULAR_PWD}/expat-2.2.4
DBUS_RUNTIME_SRC_PATH=${REGULAR_PWD}/capicxx-dbus-runtime
CORE_RUNTIME_SRC_PATH=${REGULAR_PWD}/capicxx-core-runtime
USES_LIBS_DIR=${REGULAR_PWD}/Uses_libs

DBUS_RUNTIME_BUILD_PATH=${DBUS_RUNTIME_SRC_PATH}/build
CORE_RUNTIME_BUILD_PATH=${CORE_RUNTIME_SRC_PATH}/build
EXPAT_BUILD=${EXPAT_SRC_PATH}/build
EXPAT_FINAL=${EXPAT_SRC_PATH}/final
DBUS_BUILD=${DBUS_SRC_PATH}/build
DBUS_FINAL=${DBUS_SRC_PATH}/final

PATCHFILES=$(wildcard ${DBUS_RUNTIME_SRC_PATH}/src/dbus-patches/*.patch)

PKG_CONFIG_PATH=${EXPAT_FINAL}/lib/pkgconfig:${DBUS_SRC_PATH}:${CORE_RUNTIME_BUILD_PATH}


all: copy_libraries
	#${TIMESTAMPS}/build_dirs_created.timestamp 
	#copy_libraries

${TIMESTAMPS}/timestamp_dir_created.timestamp:	
	mkdir -p ${TIMESTAMPS}
	touch $@

${TIMESTAMPS}/unzip.timestamp: 	${TIMESTAMPS}/timestamp_dir_created.timestamp
	tar -xzf ${SOURCES_DIR}/dbus-1.10.10.tar.gz
	
	unzip -q -o ${SOURCES_DIR}/capicxx-dbus-runtime-master.zip
	mv ./capicxx-dbus-runtime-master ./capicxx-dbus-runtime
	
	unzip -q -o ${SOURCES_DIR}/capicxx-core-runtime-master.zip
	mv ./capicxx-core-runtime-master ./capicxx-core-runtime
	
	tar xfj ${SOURCES_DIR}/expat-2.2.4.tar.bz2
	
	touch $@


${TIMESTAMPS}/build_dirs_created.timestamp: ${TIMESTAMPS}/unzip.timestamp
	mkdir -p ${DBUS_RUNTIME_BUILD_PATH}
	mkdir -p ${CORE_RUNTIME_BUILD_PATH}
	mkdir -p ${EXPAT_BUILD}
	mkdir -p ${EXPAT_FINAL}
	mkdir -p ${DBUS_BUILD}
	mkdir -p ${DBUS_FINAL}
	touch $@


${EXPAT_FINAL}/lib/libexpat.so:		${TIMESTAMPS}/build_dirs_created.timestamp
	cd ${EXPAT_BUILD}; \
	${EXPAT_SRC_PATH}/configure ${CONFIGURE_FLAGS} --prefix=${EXPAT_FINAL}; \
	make -j4; \
	make install




${TIMESTAMPS}/patch_dbus.timestamp: 	${TIMESTAMPS}/build_dirs_created.timestamp
	cd ${DBUS_SRC_PATH}; \
	$(foreach file, $(PATCHFILES), patch -p1 < $(file); )
	touch $@

	


${CORE_RUNTIME_BUILD_PATH}/libCommonAPI.so: 	${EXPAT_FINAL}/lib/libexpat.so 
	cd ${CORE_RUNTIME_BUILD_PATH};  \
	cmake .. -DCMAKE_INSTALL_PREFIX=${CORE_RUNTIME_BUILD_PATH}; \
	make -j4; \
	make install
	mv ${CORE_RUNTIME_BUILD_PATH}/include/CommonAPI-3.1/* ${CORE_RUNTIME_BUILD_PATH}/include




${DBUS_FINAL}/usr/local/lib/libdbus-1.so:	${TIMESTAMPS}/patch_dbus.timestamp \
						${CORE_RUNTIME_BUILD_PATH}/libCommonAPI.so
	cd ${DBUS_BUILD}; \
	${DBUS_SRC_PATH}/configure ${CONFIGURE_FLAGS} --enable-tests=no --enable-modular-tests=no; \
	make -j4; \
	make install DESTDIR=${DBUS_FINAL}


${DBUS_RUNTIME_BUILD_PATH}/libCommonAPI-DBus.so: ${DBUS_FINAL}/usr/local/lib/libdbus-1.so
	export PKG_CONFIG_PATH=${DBUS_FINAL}/usr/local/lib/pkgconfig; \
	cd ${DBUS_RUNTIME_BUILD_PATH}; \
	cmake .. -DUSE_INSTALLED_COMMONAPI=OFF \
		-DUSE_INSTALLED_DBUS=OFF \
		-DDBus_INCLUDE_DIRS="${DBUS_FINAL}/usr/local/include/dbus-1.0;${DBUS_FINAL}/usr/local/lib/dbus-1.0/include" \
		-DCMAKE_PREFIX_PATH=${CORE_RUNTIME_BUILD_PATH}; \
	make -j4

${TIMESTAMPS}/libraries_copied.timestamp:	${DBUS_RUNTIME_BUILD_PATH}/libCommonAPI-DBus.so
	mkdir -p ${USES_LIBS_DIR}
	cp ${DBUS_RUNTIME_BUILD_PATH}/*.so 	${USES_LIBS_DIR}
	cp ${DBUS_RUNTIME_BUILD_PATH}/*.so.* 	${USES_LIBS_DIR}
	cp ${CORE_RUNTIME_BUILD_PATH}/*.so 	${USES_LIBS_DIR}
	cp ${CORE_RUNTIME_BUILD_PATH}/*.so.* 	${USES_LIBS_DIR}
	#cp ${DBUS_FINAL}/usr/local/lib/*.so	${USES_LIBS_DIR} # not working then?
	#cp ${DBUS_FINAL}/usr/local/lib/*.so.*	${USES_LIBS_DIR} # not working then?
	#cp ${EXPAT_FINAL}/lib/.so		${USES_LIBS_DIR}
	#cp ${EXPAT_FINAL}/lib/.so.*		${USES_LIBS_DIR}
	touch $@

CommonAPI:	${DBUS_RUNTIME_BUILD_PATH}/libCommonAPI-DBus.so

copy_libraries:	${TIMESTAMPS}/libraries_copied.timestamp

clean:
	rm -rf ./*/

.SILENT:

#.ONESHELL:

