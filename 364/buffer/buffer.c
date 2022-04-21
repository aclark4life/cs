#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define PERMS 0666
#define BUF_SIZE 700
#define BUFFER_ADDRESS &buffer
#define DATA_INDEX_ADDRESS &data_index
#define SWITCH WHICH = !WHICH
/*******************************************************************/

void create_outfiles();
void close_files();
void malloc_buffer(char ***m_buffer);
void init_buffer_index(int *s_index, int *d_index, int *f_index, int *c_index);
void write_buff(char buff[BUF_SIZE], int fd);
void get_write_fd(int *a, int *b, int *c, int *d);
int get_read_fd(char *file);
int find_char_bjubb(char find_me, char ***buffer, int position, int *which);
void init_start_values(char ***buffer, int *data_index, int *format_index,
                       int *format_count, int *which, int *data_which);
void do_string(int length, char ***buffer, int fd, char buff[BUF_SIZE],
               int *data_index, int *s_index, int *which, int *data_which);
void do_int(int length, char ***buffer, int fd, char buff[BUF_SIZE],
            int *data_index, int *d_index, int *which, int *data_which);
void do_char(char ***buffer, int fd, char buff[BUF_SIZE], int *data_index,
             int *c_index, int *data_which);
void do_float(int length1, int length2, char ***buffer, int fd,
              char buff[BUF_SIZE], int *data_index, int *f_index, int *which,
              int *data_which);
void check_buff(int *output_buffer_index, char output_buff[BUF_SIZE], int *fd);
void read_input_data_bjubb(int fd, char ***buffer);
void flush_buff(char buffer[BUF_SIZE]);

/*******************************************************************/
int main(int argc, char *argv[]) {
  char *INFILE = argv[1];
  char **buffer;
  char s_buffer[BUF_SIZE];
  char d_buffer[BUF_SIZE];
  char f_buffer[BUF_SIZE];
  char c_buffer[BUF_SIZE];

  int n, m, i, j, s, d, f, c;
  int s_index, d_index, f_index, c_index;
  int s_length, d_length, f_length1, f_length2, c_length;
  int format_index;
  int format_count;
  int data_index;
  int infile = 0;
  int WHICH = 0;
  int data_WHICH = 0;
  if (argc != 2) {
    write(2, "Usage: ", 7);
    write(2, argv[0], strlen(argv[0]));
    write(2, " <infile>\n", 10);
    exit(-1);
  }

  if (infile == get_read_fd(INFILE)) {
    write(2, argv[0], strlen(argv[0]));
    write(2, " error: infile is NULL.\n", 24);
    exit(-1);
  }
  malloc_buffer(&buffer);
  init_buffer_index(&s_index, &d_index, &f_index, &c_index);
  create_outfiles();
  get_write_fd(&s, &d, &f, &c);
  infile = get_read_fd(INFILE);
  read_input_data_bjubb(infile, &buffer);
  init_start_values(BUFFER_ADDRESS, DATA_INDEX_ADDRESS, &format_index,
                    &format_count, &WHICH, &data_WHICH);
  /*******************************************************************/
  for (j = 0; j < (format_count + 1); j++) {
    if (j == (BUF_SIZE)) {
      SWITCH;
      format_index = 0;
    }
    switch (buffer[WHICH][format_index]) {
    case '(':
      format_index++;
      break;
    case 's':
      s_length = buffer[WHICH][format_index + 1];
      do_string(s_length, BUFFER_ADDRESS, s, s_buffer, DATA_INDEX_ADDRESS,
                &s_index, &WHICH, &data_WHICH);
      j++;
      format_index += 2;
      break;
    case 'd':
      d_length = buffer[WHICH][format_index + 1];
      do_int(d_length, BUFFER_ADDRESS, d, d_buffer, DATA_INDEX_ADDRESS,
             &d_index, &WHICH, &data_WHICH);
      j++;
      format_index += 2;
      break;
    case 'f':
      f_length1 = buffer[WHICH][format_index + 1];
      f_length2 = buffer[WHICH][format_index + 3];
      do_float(f_length1, f_length2, BUFFER_ADDRESS, f, f_buffer,
               DATA_INDEX_ADDRESS, &f_index, &WHICH, &data_WHICH);
      j += 3;
      format_index += 4;
      break;
    case 'c':
      do_char(BUFFER_ADDRESS, c, c_buffer, DATA_INDEX_ADDRESS, &c_index,
              &data_WHICH);
      format_index++;
      break;
    case ')':
      format_index = data_index;
      if (find_char_bjubb('(', BUFFER_ADDRESS, data_index, &WHICH) == 0) {
        break;
      } else {
        data_index =
            find_char_bjubb(')', BUFFER_ADDRESS, data_index, &data_WHICH) + 1;
        j = 0;
        format_count = data_index;
      }
      break;
    default:
      break;
    }
  }
  write_buff(f_buffer, f);
  write_buff(s_buffer, s);
  write_buff(d_buffer, d);
  write_buff(c_buffer, c);
  close_files();
}
/*******************************************************************/
void init_start_values(char ***buffer, int *data_index, int *format_index,
                       int *format_count, int *which, int *data_which) {
  int i, j;
  /* found EOF */
  for (i = 0; i < BUF_SIZE; i++) {
    for (j = 0; j < (BUF_SIZE); j++) {
      if ((*buffer)[*data_which][j] == ')') {
        (*data_index)++;
        // return (1);
      } else {
        (*data_index)++;
        (*format_count)++;
      }
    }
    (*data_index) = 0;
    (*data_which) = !(*data_which);
  }
}
/*******************************************************************/
void do_string(int length, char ***in, int fd, char s_buffer[BUF_SIZE],
               int *data_index, int *s_buffer_index, int *which,
               int *data_which) {
  int i, j;
  int stop;
  if ((*data_index) == BUF_SIZE) {
    (*data_index) = 0;
    (*data_which) = !(*data_which);
  }
  check_buff(s_buffer_index, s_buffer, &fd);
  s_buffer[*s_buffer_index] = '(';
  (*s_buffer_index)++;

  check_buff(s_buffer_index, s_buffer, &fd);
  s_buffer[(*s_buffer_index)] = 's';
  (*s_buffer_index)++;

  check_buff(s_buffer_index, s_buffer, &fd);
  s_buffer[(*s_buffer_index)] = length;
  (*s_buffer_index)++;

  check_buff(s_buffer_index, s_buffer, &fd);
  s_buffer[(*s_buffer_index)] = ')';
  (*s_buffer_index)++;

  length = length - '0';
  stop = (*data_index) + length;

  for (i = (*data_index), j = (*s_buffer_index); i < stop; i++, j++) {
    check_buff(s_buffer_index, s_buffer, &fd);
    s_buffer[j] = (*in)[*data_which][i];
  }
  (*data_index) = stop;
  (*s_buffer_index) = j;
}
/*******************************************************************/
void do_int(int length, char ***in, int fd, char d_buffer[BUF_SIZE],
            int *data_index, int *d_buffer_index, int *which, int *data_which) {
  int i;
  int j;
  int stop;

  if ((*data_index) == BUF_SIZE) {
    (*data_index) = 0;
    (*data_which) = !(*data_which);
  }

  check_buff(d_buffer_index, d_buffer, &fd);
  d_buffer[*d_buffer_index] = '(';
  (*d_buffer_index)++;

  check_buff(d_buffer_index, d_buffer, &fd);
  d_buffer[(*d_buffer_index)] = 'd';
  (*d_buffer_index)++;

  check_buff(d_buffer_index, d_buffer, &fd);
  d_buffer[(*d_buffer_index)] = length;
  (*d_buffer_index)++;

  check_buff(d_buffer_index, d_buffer, &fd);
  d_buffer[(*d_buffer_index)] = ')';
  (*d_buffer_index)++;

  length = length - '0';
  stop = (*data_index) + length;
  for (i = (*data_index), j = (*d_buffer_index); i < stop; i++, j++) {
    check_buff(d_buffer_index, d_buffer, &fd);
    d_buffer[j] = (*in)[*data_which][i];
  }
  (*data_index) = stop;
  (*d_buffer_index) = j;
}
/*******************************************************************/
void do_float(int length1, int length2, char ***in, int fd,
              char f_buffer[BUF_SIZE], int *data_index, int *f_buffer_index,
              int *which, int *data_which) {
  int i, j, stop1, stop2;
  *f_buffer_index;

  if ((*data_index) == BUF_SIZE) {
    (*data_index) = 0;
    (*data_which) = !(*data_which);
  }

  check_buff(f_buffer_index, f_buffer, &fd);
  f_buffer[*f_buffer_index] = '(';
  (*f_buffer_index)++;

  check_buff(f_buffer_index, f_buffer, &fd);
  f_buffer[*f_buffer_index] = 'f';
  (*f_buffer_index)++;

  check_buff(f_buffer_index, f_buffer, &fd);
  f_buffer[*f_buffer_index] = length1;
  (*f_buffer_index)++;

  check_buff(f_buffer_index, f_buffer, &fd);
  f_buffer[*f_buffer_index] = '.';
  (*f_buffer_index)++;

  check_buff(f_buffer_index, f_buffer, &fd);
  f_buffer[*f_buffer_index] = length2;
  (*f_buffer_index)++;

  check_buff(f_buffer_index, f_buffer, &fd);
  f_buffer[*f_buffer_index] = ')';
  (*f_buffer_index)++;

  length1 = length1 - '0';
  length2 = length2 - '0';

  stop1 = (*data_index) + length1;
  stop2 = stop1 + length2;

  for (i = (*data_index), j = (*f_buffer_index); i < stop1; i++, j++) {
    check_buff(f_buffer_index, f_buffer, &fd);
    f_buffer[j] = (*in)[*data_which][i];
  }

  (*data_index) = stop1;
  for (i = (*data_index); i < stop2; i++, j++) {
    check_buff(f_buffer_index, f_buffer, &fd);
    f_buffer[j] = (*in)[*data_which][i];
  }

  (*f_buffer_index) = j;
  (*data_index) = stop2;
}
/*******************************************************************/
void do_char(char ***in_buff, int fd, char c_buffer[BUF_SIZE], int *data_index,
             int *c_buffer_index, int *data_which) {
  if ((*data_index) == BUF_SIZE) {
    (*data_index) = 0;
    (*data_which) = !(*data_which);
  }

  check_buff(c_buffer_index, c_buffer, &fd);
  c_buffer[*c_buffer_index] = '(';
  (*c_buffer_index)++;

  check_buff(c_buffer_index, c_buffer, &fd);
  c_buffer[*c_buffer_index] = 'c';
  (*c_buffer_index)++;

  check_buff(c_buffer_index, c_buffer, &fd);
  c_buffer[*c_buffer_index] = ')';
  (*c_buffer_index)++;

  check_buff(c_buffer_index, c_buffer, &fd);
  c_buffer[*c_buffer_index] = (*in_buff)[*data_which][*data_index];

  (*c_buffer_index)++;
  (*data_index)++;
}
/*******************************************************************/
void check_buff(int *output_buffer_index, char output_buff[BUF_SIZE],
                int *fd) { /* what the hell am i doing in here...oh yeah...

                              checking to see if it is time to empty
                              the output buffer.

                              ie. if i have placed BUF_SIZE number of things
                              into the output buffer, then it is time to write
                              it to a file...

                              must flush buffer...
                              */
  int i;
  if ((*output_buffer_index) == BUF_SIZE) {
    write_buff(output_buff, *fd);
    flush_buff(output_buff);
    *output_buffer_index = 0;
  }
}
/*******************************************************************/
void malloc_buffer(char ***m_buffer) {
  int i;
  *m_buffer = (char **)malloc(sizeof(char *) * 2);
  for (i = 0; i < BUF_SIZE; i++)
    (*m_buffer)[i] = (char *)malloc(sizeof(char) * BUF_SIZE);
}
/*******************************************************************/
void init_buffer_index(int *sindex, int *dindex, int *findex, int *cindex) {
  *sindex = 0;
  *dindex = 0;
  *findex = 0;
  *cindex = 0;
}
/*******************************************************************/
void write_buff(char buff[BUF_SIZE], int fd) { write(fd, buff, BUF_SIZE); }
/*******************************************************************/
int get_read_fd(char *file) {
  int fd;
  fd = open(file, O_RDONLY, PERMS);
  return (fd);
}
/*******************************************************************/
void get_write_fd(int *a, int *b, int *c, int *d) {
  *a = open("s.out", O_WRONLY, PERMS);
  *b = open("d.out", O_WRONLY, PERMS);
  *c = open("f.out", O_WRONLY, PERMS);
}
/*******************************************************************/
void create_outfiles() {
  creat("s.out", PERMS);
  creat("d.out", PERMS);
  creat("f.out", PERMS);
  creat("c.out", PERMS);
}
/*******************************************************************/
void close_files() {
  close(*"s.out");
  close(*"d.out");
  close(*"f.out");
  close(*"c.out");
}
/*******************************************************************/
int find_char_bjubb(char find_me, char ***buffer, int position,
                    int *data_which) {
  int i = position;
  int count = 0;
  while (i < BUF_SIZE) {
    if ((*buffer)[*data_which][i] == find_me)
      return (i);
    else
      i++;
  }
  return (0);
}
/*******************************************************************/
void read_input_data_bjubb(int fd, char ***buffer) {
  int check = 0, read_count = 0, n_bytes = 0, which = 0;
  while (abs(read_count) <= ((BUF_SIZE * 2) - 1)) {
    if (check != read_count) {
      return; /* input at EOF */
    }
    if (abs(n_bytes) == BUF_SIZE) {
      which = (0 ? 0 : 1);
      n_bytes = 0;
    }
    read_count += read(fd, (*buffer)[which] + abs(n_bytes), 1);
    n_bytes++;
    check++;
  }
}
/*******************************************************************/
void flush_buff(char buffer[BUF_SIZE]) {

  int i;
  for (i = 0; i < BUF_SIZE; i++)
    buffer[i] = ' ';
}
/*******************************************************************/
