"""Sphinx configuration file."""

from __future__ import annotations

project = "QDMI"
author = "MQSS Development Team"
language = "en"
version = "0.1.0"
release = "0.1.0"
project_copyright = "2024, MQSS Development Team"

master_doc = "index"

templates_path = ["_templates"]
html_css_files = []

extensions = [
    "myst_parser",
    "sphinx.ext.intersphinx",
    "sphinx_copybutton",
    "sphinxext.opengraph",
    "sphinx.ext.viewcode",
    "breathe",
]

source_suffix = [".rst", ".md"]

exclude_patterns = [
    "_build",
    "**.ipynb_checkpoints",
    "**.jupyter_cache",
    "**jupyter_execute",
    "Thumbs.db",
    ".DS_Store",
    ".env",
    ".venv",
]

pygments_style = "colorful"

intersphinx_mapping = {
    "python": ("https://docs.python.org/3", None),
    "qiskit": ("https://docs.quantum.ibm.com/api/qiskit", None),
    "mqt": ("https://mqt.readthedocs.io/en/latest", None),
}

myst_enable_extensions = [
    "amsmath",
    "colon_fence",
    "substitution",
    "deflist",
    "dollarmath",
]
myst_heading_anchors = 3

copybutton_prompt_text = r"(?:\(\.?venv\) )?(?:\[.*\] )?\$ "
copybutton_prompt_is_regexp = True
copybutton_line_continuation_character = "\\"

breathe_projects = {
    "qdmi": "doxygen/xml",
}
breathe_default_project = "qdmi"
breathe_domain_by_extension = {
    "h" : "c",
    "c" : "c",
}
breathe_projects_source = {
    "qdmi": (
        "../include/qdmi", [
            "return_codes.h",
            "properties.h",
            "interface.h",
            "backend.h",
            "backend/control.h",
            "backend/query.h",
            "interface/query.h",
            "interface/session.h",
            "private/_device.h",
            "private/_types.h",
        ]
    )
}
breathe_show_enumvalue_initializer = True

# -- Options for HTML output -------------------------------------------------
html_theme = "furo"
html_static_path = ["_static"]
html_theme_options = {
    "light_logo": "mqss_logo.png",
    "dark_logo": "mqss_logo.png",
    "source_repository": "https://github.com/Munich-Quantum-Software-Stack/QDMI",
    "source_branch": "develop",
    "source_directory": "docs/",
    "navigation_with_keys": True,
}
