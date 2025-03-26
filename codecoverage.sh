#!/bin/bash

lcov -v -t "tst_viasyncworker" --ignore mismatch --include "core*" --include "tests*" -o tst_viasyncworker.info -c -d . && \
genhtml -o report tst_viasyncworker.info
