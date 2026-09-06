# SPDX-FileContributor: Joshua Watt
# SPDX-FileCopyrightText: 2024 Joshua Watt
# SPDX-FileType: SOURCE
# SPDX-License-Identifier: MIT
"""spdx3-validate: SPDX 3 validation library and CLI tool."""

from .core import (
    Document,
    SpdxValidateError,
    UnknownVersionError,
    ValidationError,
    ValidationResult,
    validate,
)
from .main import spdx3validate
from .version import VERSION as __version__

__all__ = [
    "__version__",
    "validate",
    "ValidationResult",
    "ValidationError",
    "Document",
    "SpdxValidateError",
    "UnknownVersionError",
    "spdx3validate",
]
