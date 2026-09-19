# CS 496 - Capstone / Networking

Capstone coursework centered on network services: a BOOTP/DHCP server implementation and a small Perl-based CGI web search application, plus software-engineering ethics/paper-review readings.

## Networking

### bootp.c / bootp.pl / bootp.perl / bootptab
A BOOTP (Bootstrap Protocol) server: `bootp.c` is a C-based parser/experiment, `bootp.pl`/`bootp.perl` are Perl implementations (adapted from a script provided by Bruce Duncan), and `bootptab` is a sample client configuration table. `bootp.html`/`bootp.bak.html` document the project.

### dhcp/, httpd/, cc/, gcc/, ns/, perl/
Placeholder directories referencing the DHCP server, HTTP server, and toolchain (C compiler, GCC, `ns` network simulator, Perl) used/targeted by this coursework.

## Web / CGI

### form.html / form.pl / search.html / search.pl / start.html / end.html / index.html
A simple Perl CGI form-and-search web application: `form.pl` collects input, `search.pl` searches a data file for matches, with `httpd.conf`/`srm.conf`/`access.conf`/`localhost_srm.conf` as the accompanying Apache/NCSA httpd configuration.

## Readings

### killer-robot.txt
"The Case of the Killer Robot" — a software engineering/computer ethics case study.

### paper-review-kbg.txt
A review of an IEEE Computer paper, written for Dr. Keith Gallagher.

### cisco.html / nt.html / dhcp.html / httpd.html
Notes/documentation on Cisco routers, Windows NT, DHCP, and httpd administration.
