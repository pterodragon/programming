find_path(CXX_PRETTYPRINT_DIR NAMES prettyprint.hpp
        HINTS "${THIRD_PARTY_DIR}/cxx-prettyprint"
        )
find_package_handle_standard_args(cxx_prettyprint
    "cxx-prettyprint not found"
    CXX_PRETTYPRINT_DIR
    )
mark_as_advanced(CXX_PRETTYPRINT_DIR)
