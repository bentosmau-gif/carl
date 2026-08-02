#ifndef CARL_COMMANDS_H
#define CARL_COMMANDS_H

void c_cmd_dir(const char* path);
void c_cmd_cd(const char* path);
void c_cmd_copy(const char* src, const char* dest);
void c_cmd_del(const char *filename);
void c_cmd_mkdir(const char *dirname);
void c_cmd_rmdir(const char *dirname);
void c_cmd_type(const char *filename);
void c_cmd_cls(void);
void c_cmd_exit(void);

#endif // CARL_COMMANDS_H