# fidl generation

FIDL_GEN_TIMESTAMP	=    fidl_gen.timestamp
FIDL_FILE  	= ../fidl/E00HelloWorld.fidl

TOOLS_FOLDER 		= ../../tools/Sources
TOOLS_SOURCES_FOLDER 	= ../../tools/Sources

DEST_DIR_FIDL	= ./interfaces

COMMONAPI_CORE=commonapi-generator
COMMONAPI_DBUS=commonapi_dbus_generator
DIR_BIN_COMMONAPI_GENERATOR 		= ${TOOLS_FOLDER}/${COMMONAPI_CORE}
DIR_BIN_COMMONAPI_DBUS_GENERATOR 	= ${TOOLS_FOLDER}/${COMMONAPI_DBUS}

BIN_COMMONAPI_GENERATOR 	= ${DIR_BIN_COMMONAPI_GENERATOR}/commonapi-generator-linux-x86_64
BIN_COMMONAPI_DBUS_GENERATOR 	= ${DIR_BIN_COMMONAPI_DBUS_GENERATOR}/commonapi-dbus-generator-linux-x86_64


all: ${FIDL_GEN_TIMESTAMP}


${BIN_COMMONAPI_GENERATOR}:
	unzip -q -o ${TOOLS_SOURCES_FOLDER}/${COMMONAPI_CORE}.zip 	-d ${TOOLS_FOLDER}/${COMMONAPI_CORE}; \
	touch $@

${BIN_COMMONAPI_DBUS_GENERATOR}:
	unzip -q -o ${TOOLS_SOURCES_FOLDER}/${COMMONAPI_DBUS}.zip 	-d ${TOOLS_FOLDER}/${COMMONAPI_DBUS}; \
	touch $@


${FIDL_GEN_TIMESTAMP}: ${FIDL_FILE} ${BIN_COMMONAPI_GENERATOR} ${BIN_COMMONAPI_DBUS_GENERATOR}
	rm -rf ${DEST_DIR_FIDL}
	mkdir -p ${DEST_DIR_FIDL}
	echo "--------------------------------------------------"	
	${BIN_COMMONAPI_GENERATOR}      -sk ${FIDL_FILE} --dest ${DEST_DIR_FIDL}
	echo "--------------------------------------------------"
	${BIN_COMMONAPI_DBUS_GENERATOR}	    ${FIDL_FILE} --dest ${DEST_DIR_FIDL}
	echo "--------------------------------------------------"
	echo "Done!"
	echo
	touch $@


.SILENT:
