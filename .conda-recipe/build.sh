export LIB_NAME=ClosedStepper
# Make Arduino library directory (and parent directories, if necessary).
mkdir -p "${PREFIX}"/include/Arduino
# Copy library source files into Arduino library directory.
cp -ra "${SRC_DIR}" "${PREFIX}"/include/Arduino/${LIB_NAME}
rm "${PREFIX}"/include/Arduino/${LIB_NAME}/build.sh
rc=$?; if [[ $rc != 0  ]]; then exit $rc; fi
