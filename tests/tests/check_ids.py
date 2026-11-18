#!/usr/bin/env python3
# SPDX-License-Identifier: Apache-2.0
# Copyright (c) Bao Project and Contributors. All rights reserved.

"""
Check that every KAO_TEST id under tests/src follows the CC_SS_FF_TT scheme
described in tests/README.md and matches the location of its file.
"""

import os
import re
import sys

CATEGORIES = {"00_generic": "00", "01_arch": "01", "02_platform": "02"}

_C_TOKEN_RE = re.compile(
    r'"(?:\\.|[^"\\])*"|//[^\r\n]*|/\*.*?(?:\*/|$)',
    re.DOTALL,
)
_KAO_TEST_RE = re.compile(r"\bKAO_TEST\s*\(\s*([^,\s]+)\s*,")
_ID_RE = re.compile(r"^(\d\d)_(\d\d)_(\d\d)_(\d\d)$")
_PREFIX_RE = re.compile(r"^(\d+)_")


def _strip_comments(source):
    def replace(match):
        token = match.group(0)
        if token.startswith('"'):
            return token
        return re.sub(r"[^\r\n]", " ", token)
    return _C_TOKEN_RE.sub(replace, source)


def expected_prefix(rel_path):
    """CC_SS_FF prefix implied by a file's location; ValueError when misplaced."""
    parts = rel_path.split(os.sep)
    category = CATEGORIES.get(parts[0])
    if category is None:
        raise ValueError(f"not under one of {', '.join(CATEGORIES)}")

    file_match = _PREFIX_RE.match(parts[-1])
    if category == "00":
        if len(parts) != 2 or file_match is None or len(file_match.group(1)) != 4:
            raise ValueError(
                "generic tests must be FFFF_name.c files directly under 00_generic"
            )
        digits = file_match.group(1)
        return f"{category}_{digits[:2]}_{digits[2:]}"

    if len(parts) < 3:
        raise ValueError(f"{parts[0]} tests must live under {parts[0]}/SS_<name>/")
    scope_match = _PREFIX_RE.match(parts[1])
    if scope_match is None or len(scope_match.group(1)) != 2:
        raise ValueError(f"subdirectory '{parts[1]}' must be named SS_<name>")
    if file_match is None or len(file_match.group(1)) != 2:
        raise ValueError(f"file '{parts[-1]}' must be named FF_name.c")
    return f"{category}_{scope_match.group(1)}_{file_match.group(1)}"


def check(src_root):
    """Return a list of problems found under src_root."""
    problems = []
    seen = {}
    for root, dirs, files in os.walk(src_root):
        dirs.sort()
        for fname in sorted(files):
            if not fname.endswith(".c"):
                continue
            path = os.path.join(root, fname)
            rel_path = os.path.relpath(path, src_root)
            with open(path, "r", encoding="utf8") as c_file:
                source = _strip_comments(c_file.read())

            ids = _KAO_TEST_RE.findall(source)
            if not ids:
                continue
            try:
                prefix = expected_prefix(rel_path)
            except ValueError as exc:
                problems.append(f"{rel_path}: {exc}")
                continue

            for test_id in ids:
                if not _ID_RE.match(test_id):
                    problems.append(f"{rel_path}: id '{test_id}' is not CC_SS_FF_TT")
                elif not test_id.startswith(prefix + "_"):
                    problems.append(
                        f"{rel_path}: id '{test_id}' does not match its location "
                        f"(expected {prefix}_TT)"
                    )
                if test_id in seen:
                    problems.append(
                        f"{rel_path}: id '{test_id}' already used in {seen[test_id]}"
                    )
                seen.setdefault(test_id, rel_path)
    return problems


def main(argv):
    """Check the tree given as first argument (default: src next to this script)."""
    src_root = argv[1] if len(argv) > 1 else os.path.join(os.path.dirname(__file__), "src")
    problems = check(os.path.abspath(src_root))
    for problem in problems:
        print(f"check_ids: {problem}")
    if problems:
        return 1
    print(f"check_ids: all test ids under {src_root} are valid")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
