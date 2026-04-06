# Configuration file for the Sphinx documentation builder.

import subprocess

project = "CS Portfolio"
copyright = '1995-1999, Jeffrey "Alex" Clark'
author = 'Jeffrey "Alex" Clark'

try:
    _git_hash = subprocess.check_output(
        ["git", "rev-parse", "--short", "HEAD"],
        stderr=subprocess.DEVNULL,
    ).decode().strip()
except Exception:
    _git_hash = "unknown"

release = f"1999 ({_git_hash})"

extensions = []

templates_path = ["_templates"]
exclude_patterns = ["_build", "Thumbs.db", ".DS_Store"]

html_theme = "furo"
html_static_path = ["_static"]

html_theme_options = {
    "sidebar_hide_name": False,
}
