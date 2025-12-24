#define Result(T, E)                                                           \
  struct {                                                                     \
    bool : ok;                                                                 \
    union {                                                                    \
      T val;                                                                   \
      E err;                                                                   \
    };                                                                         \
  }

#define DEFINE_RESULT(Name, T, E)                                              \
  typedef struct {                                                             \
    bool ok;                                                                   \
    union {                                                                    \
      T val;                                                                   \
      E err;                                                                   \
    };                                                                         \
  } Name

#define Ok(Name, v) ((Name){.ok = true, .val = (v)})

#define Err(Name, e) ((Name){.ok = false, .err = (e)})
