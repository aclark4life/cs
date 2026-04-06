# Configuration file for the Sphinx documentation builder.

project = "CS Portfolio"
copyright = '1995-1999, Jeffrey "Alex" Clark'
author = 'Jeffrey "Alex" Clark'
release = "1999"

extensions = []

templates_path = ["_templates"]
exclude_patterns = ["_build", "Thumbs.db", ".DS_Store"]

html_theme = "furo"
html_static_path = ["_static"]

html_theme_options = {
    "sidebar_hide_name": False,
}
