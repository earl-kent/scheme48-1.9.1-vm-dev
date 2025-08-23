#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prescheme.h"
#include "scheme48vm-prelude.h"

struct image_location {
  long new_descriptor;
  long next;
};
struct table {
  long *keys;
  struct image_location **values;
  long count;
  long size;
};
struct event_type {
  long uid;
  char usedP;
  struct event_type *next;
};
static char add_more_channels(long);
static char add_external_event_types(long);
static char encode_scalar_valueUutf_16le(long, char *, long, char*, long*);
static char encode_scalar_valueUutf_16be(long, char *, long, char*, long*);
static char encode_scalar_valueUutf_8(long, char *, long, char*, long*);
static char decode_scalar_valueUutf_16le(char *, long, char*, long*, long*);
static char decode_scalar_valueUutf_16be(char *, long, char*, long*, long*);
static char decode_scalar_valueUutf_8(char *, long, char*, long*, long*);
static char integerLE(long, long);
static char integerGE(long, long);
static char shared_binding_undefinedP(long);
static void enqueue_channelB(long, long, long);
static long make_blank_return_code(long, long, long, long, long);
static long close_channelB(long);
static void copy_vm_string_to_stringUlatin_1B(long, long, long, char*);
static void decodeUutf_8B(char *, long, long);
static void decodeUutf_16beB(char *, long, long);
static void decodeUutf_16leB(char *, long, long);
static char not_record_typeP(long);
static long enter_bignum(char *);
static char integerE(long, long);
static long add_log_entryAgc(long, long, long, long, long, char);
static long make_channel(long, long, long, long, long, long, long, long);
static long enter_stringAgc_n(char*, long);
static long write_vm_string(long, FILE *);
static long Haction5350(long);
static long current_code_vector(void);
static void channel_close_error(long, long, long);
static long integer_bit_count(long);
static long integer_add(long, long);
static long integer_subtract(long, long);
static long integer_multiply(long, long);
static char integer_divide(long, long, long*, long*, long*, long*);
static long integer_bitwise_not(long);
static long integer_bitwise_and(long, long);
static long integer_bitwise_ior(long, long);
static long integer_bitwise_xor(long, long);
static long Hinteger_op8731(long, long);
static long Hinteger_op8662(long, long);
static char for_each_imported_binding(char(*)(long));
static long really_preserve_continuation(long);
static void push_exception_setupB(long, long);
static long Hlookup853(long, long, long);
static long Hlookup834(long, long, long);
static void HtopD12305(char, char);
static void HtopD12316(void);
void s48_set_native_protocolB(long);
void s48_set_extension_valueB(long);
long s48_channel_count(void);
long *s48_channels(void);
long s48_imported_bindings(void);
long s48_exported_bindings(void);
char s48_os_signal_pending(void);
long s48_symbol_table(void);
char * s48_set_gc_roots_baseB(void);
char s48_release_gc_roots_baseB(char *);
void s48_reset_external_rootsB(void);
char s48_external_event_readyPUunsafe(void);
void s48_note_event(void);
void s48_reset_interruptsB(void);
void s48_disable_interruptsB(void);
void s48_add_os_signal(long);
void s48_push_gc_rootsB(char *, long);
char * s48_register_gc_rootB(char *);
char s48_external_event_pendingPUunsafe(void);
long s48_dequeue_external_eventBUunsafe(char*);
void s48_note_external_eventBUunsafe(long);
void s48_stack_setB(long, long);
long s48_stack_ref(long);
void s48_push(long);
long s48_resetup_external_exception(long, long);
char s48_pop_gc_rootsB(void);
void s48_unregister_gc_rootB(char *);
char * s48_shorten_bignum(char *, long);
long s48_allocate_bignum(long);
void s48_enable_interruptsB(void);
long s48_allocate_string(long);
long s48_set_channel_os_index(long, long);
long s48_integer_or_floanum_L(long, long);
long s48_integer_or_floanum_G(long, long);
long s48_integer_or_floanum_LE(long, long);
long s48_integer_or_floanum_GE(long, long);
long s48_make_blank_return_code(long, long, long, long);
long s48_enter_string_utf_8(char *);
long s48_enter_string_utf_8_n(char *, long);
long s48_enter_string_utf_16beU(char *);
long s48_enter_string_utf_16be_nU(char *, long);
long s48_enter_string_utf_16leU(char *);
long s48_enter_string_utf_16le_nU(char *, long);
long s48_integer_or_floanum_E(long, long);
void s48_close_channel(long);
long s48_enter_string_latin_1_n(char*, long);
void s48_string_set(long, long, long);
long s48_string_ref(long, long);
long s48_string_length(long);
void s48_copy_latin_1_to_string_n(char*, long, long);
void s48_copy_latin_1_to_string(char*, long);
void s48_copy_string_to_latin_1(long, char*);
void s48_copy_string_to_latin_1_n(long, long, long, char*);
long s48_string_utf_8_length(long);
long s48_string_utf_8_length_n(long, long, long);
long s48_copy_string_to_utf_8(long, char *);
long s48_copy_string_to_utf_8_n(long, long, long, char *);
long s48_string_utf_16be_length(long);
long s48_string_utf_16be_length_n(long, long, long);
long s48_copy_string_to_utf_16beU(long, char *);
long s48_copy_string_to_utf_16be_nU(long, long, long, char *);
long s48_string_utf_16le_length(long);
long s48_string_utf_16le_length_n(long, long, long);
long s48_copy_string_to_utf_16leU(long, char *);
long s48_copy_string_to_utf_16le_nU(long, long, long, char *);
void check_stack(void);
long s48_really_add_channel(long, long, long);
long s48_enter_string_latin_1(char*);
long s48_integer_bit_count(long);
long s48_enter_integer(long);
long s48_enter_unsigned_integer(unsigned long);
long s48_integer_or_floanum_add(long, long);
long s48_integer_or_floanum_sub(long, long);
long s48_integer_or_floanum_mul(long, long);
char s48_integer_divide(long, long, long*, long*, long*, long*);
long s48_integer_bitwise_not(long);
long s48_integer_bitwise_and(long, long);
long s48_integer_bitwise_ior(long, long);
long s48_integer_bitwise_xor(long, long);
void s48_setup_external_exception(long, long);
long message_element(long, FILE *);
long s48_integer_quotient(long, long);
long s48_integer_remainder(long, long);
void s48_copy_stack_into_heap(void);
long s48_get_imported_binding(char*);
long s48_define_exported_binding(char*, long);
void s48_initialize_vm(char *, long);
void s48_post_gc_cleanup(char, char);
void s48_gc_root(void);
long s48_restart(long, long);
long s48_call_startup_procedure(char**, long);
static long Spending_interruptsS;
static long Snumber_of_channelsS;
static long *Svm_channelsS;
static long Spending_channels_headS;
static long Spending_channels_tailS;
static long *Sutf_8_state_tableS;
static long *Sutf_8_masksS;
static long Stemp0S;
static long Stemp1S;
static char * Sstack_beginS;
static char * Sstack_endS;
static char * Sreal_stack_limitS;
static char * Sbottom_of_stackS;
static long Sheap_continuationS;
static char Sstack_warningPS;
static long Simported_bindingsS;
static long Sexported_bindingsS;
static long Snumber_of_event_typesS;
static struct event_type **Sevent_typesS;
static struct event_type *Spending_event_types_headS;
static struct event_type *Spending_event_types_tailS;
static struct event_type *Spending_event_types_readyS;
static struct event_type *Sunused_event_types_headS;
static long Sexception_handlersS;
static long Sinterrupt_handlersS;
static char * Slast_code_pointer_resumedS;
static long Scurrent_threadS;
static long Ssession_dataS;
static long Sfinalizer_alistS;
static long Sfinalize_theseS;
static char Sgc_in_troublePS;
static long Senabled_interruptsS;
static long Sinterrupted_templateS;
static long Sinterrupted_byte_opcode_return_codeS;
static long Sinterrupted_native_call_return_codeS;
static long Snative_poll_return_codeS;
static long Sexception_return_codeS;
static long Snative_exception_return_codeS;
static long Scall_with_values_return_codeS;
static long Ssaved_pcS;
static long *Sos_signal_ringS;
static long Sos_signal_ring_startS;
static long Sos_signal_ring_readyS;
static long Sos_signal_ring_endS;
static char Sexternal_exceptionPS;
static long Sexternal_exception_nargsS;
static long Sthe_symbol_tableS;
static char * Sexternal_root_stackS;
static char * Sexternal_root_stack_baseS;
static char * Spermanent_external_rootsS;
static long Sempty_logS;
static void (*Spost_gc_cleanupS)(char, char);
static void (*Sgc_root_procS)(void);
char * SstackS;
char * s48_Sstack_limitS;
char * ScontS;
char * Scode_pointerS;
long SvalS;
long Slast_code_calledS;
char s48_Spending_interruptPS;
long s48_Snc_templateS;
long Snative_exception_contS;
long s48_Snative_protocolS;
long s48_Sextension_valueS;
long s48_Scallback_return_stack_blockS;
char s48_Spending_eventsPS;

static char add_more_channels(long index_7X)
{
  long arg0K0;
  long i_13X;
  long i_12X;
  long *new_vm_channels_11X;
  long new_count_10X;
  long y_9X;
  long x_8X;
 {  x_8X = 1 + index_7X;
  y_9X = 8 + (Snumber_of_channelsS);
  if ((x_8X < y_9X)) {
    arg0K0 = y_9X;
    goto L3853;}
  else {
    arg0K0 = x_8X;
    goto L3853;}}
 L3853: {
  new_count_10X = arg0K0;
  new_vm_channels_11X = (long*)malloc(sizeof(long) * new_count_10X);
  if ((NULL == new_vm_channels_11X)) {
    return 0;}
  else {
    arg0K0 = 0;
    goto L3865;}}
 L3865: {
  i_12X = arg0K0;
  if ((i_12X == (Snumber_of_channelsS))) {
    arg0K0 = (Snumber_of_channelsS);
    goto L3938;}
  else {
    *(new_vm_channels_11X + i_12X) = (*((Svm_channelsS) + i_12X));
    arg0K0 = (1 + i_12X);
    goto L3865;}}
 L3938: {
  i_13X = arg0K0;
  if ((i_13X == new_count_10X)) {
    free((Svm_channelsS));
    Svm_channelsS = new_vm_channels_11X;
    Snumber_of_channelsS = new_count_10X;
    return 1;}
  else {
    *(new_vm_channels_11X + i_13X) = 1;
    arg0K0 = (1 + i_13X);
    goto L3938;}}
}
static char add_external_event_types(long min_count_14X)
{
  long arg0K0;
  struct event_type *arg1K0;
  struct event_type *t_21X;
  struct event_type *event_type_20X;
  struct event_type *next_19X;
  long i_18X;
  struct event_type **new_event_types_17X;
  long old_count_16X;
  struct event_type **old_event_types_15X;
 {  old_event_types_15X = Sevent_typesS;
  old_count_16X = Snumber_of_event_typesS;
  new_event_types_17X = (struct event_type**)malloc(sizeof(struct event_type*) * min_count_14X);
  if ((NULL == new_event_types_17X)) {
    return 0;}
  else {
    arg0K0 = 0;
    goto L5455;}}
 L5455: {
  i_18X = arg0K0;
  if ((i_18X == min_count_14X)) {
    Sevent_typesS = new_event_types_17X;
    Snumber_of_event_typesS = min_count_14X;
    free(old_event_types_15X);
    return 1;}
  else {
    if ((i_18X < old_count_16X)) {
      *(new_event_types_17X + i_18X) = (*(old_event_types_15X + i_18X));
      arg0K0 = (1 + i_18X);
      goto L5455;}
    else {
      next_19X = Sunused_event_types_headS;
      event_type_20X = (struct event_type*)malloc(sizeof(struct event_type));
      if ((NULL == event_type_20X)) {
        arg1K0 = event_type_20X;
        goto L5471;}
      else {
        event_type_20X->uid = i_18X;
        event_type_20X->usedP = 0;
        event_type_20X->next = next_19X;
        arg1K0 = event_type_20X;
        goto L5471;}}}}
 L5471: {
  t_21X = arg1K0;
  if ((NULL == t_21X)) {
    Sevent_typesS = new_event_types_17X;
    Snumber_of_event_typesS = i_18X;
    return 0;}
  else {
    *(new_event_types_17X + i_18X) = t_21X;
    Sunused_event_types_headS = t_21X;
    arg0K0 = (1 + i_18X);
    goto L5455;}}
}
static char encode_scalar_valueUutf_16le(long value_22X, char * buffer_23X, long count_24X, char *TT0, long *TT1)
{
  long word_26X;
  long word_25X;
 {  if ((65535 < value_22X)) {
    if ((count_24X < 4)) {
      *TT0 = 1;
      *TT1 = 4;
      return 1;}
    else {
      word_25X = 55232 + (PS_SHIFT_RIGHT_LOGICAL_INLINE(value_22X, 10));
      *((unsigned char *) buffer_23X) = (unsigned char) ((255 & word_25X));
      *((unsigned char *) (buffer_23X + 1)) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE(word_25X, 8)));
      word_26X = 56320 + (1023 & value_22X);
      *((unsigned char *) (buffer_23X + 2)) = (unsigned char) ((255 & word_26X));
      *((unsigned char *) (buffer_23X + 3)) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE(word_26X, 8)));
      *TT0 = 0;
      *TT1 = 4;
      return 1;}}
  else {
    if ((count_24X < 2)) {
      *TT0 = 1;
      *TT1 = 2;
      return 1;}
    else {
      *((unsigned char *) buffer_23X) = (unsigned char) ((255 & value_22X));
      *((unsigned char *) (buffer_23X + 1)) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE(value_22X, 8)));
      *TT0 = 0;
      *TT1 = 2;
      return 1;}}}
}
static char encode_scalar_valueUutf_16be(long value_27X, char * buffer_28X, long count_29X, char *TT0, long *TT1)
{
  long word_31X;
  long word_30X;
 {  if ((65535 < value_27X)) {
    if ((count_29X < 4)) {
      *TT0 = 1;
      *TT1 = 4;
      return 1;}
    else {
      word_30X = 55232 + (PS_SHIFT_RIGHT_LOGICAL_INLINE(value_27X, 10));
      *((unsigned char *) buffer_28X) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE(word_30X, 8)));
      *((unsigned char *) (buffer_28X + 1)) = (unsigned char) ((255 & word_30X));
      word_31X = 56320 + (1023 & value_27X);
      *((unsigned char *) (buffer_28X + 2)) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE(word_31X, 8)));
      *((unsigned char *) (buffer_28X + 3)) = (unsigned char) ((255 & word_31X));
      *TT0 = 0;
      *TT1 = 4;
      return 1;}}
  else {
    if ((count_29X < 2)) {
      *TT0 = 1;
      *TT1 = 2;
      return 1;}
    else {
      *((unsigned char *) buffer_28X) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE(value_27X, 8)));
      *((unsigned char *) (buffer_28X + 1)) = (unsigned char) ((255 & value_27X));
      *TT0 = 0;
      *TT1 = 2;
      return 1;}}}
}
static char encode_scalar_valueUutf_8(long value_32X, char * buffer_33X, long count_34X, char *TT0, long *TT1)
{

 {  if ((127 < value_32X)) {
    if ((2047 < value_32X)) {
      if ((65535 < value_32X)) {
        if ((count_34X < 4)) {
          *TT0 = 1;
          *TT1 = 4;
          return 1;}
        else {
          *((unsigned char *) buffer_33X) = (unsigned char) ((240 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((1835008 & value_32X), 18))));
          *((unsigned char *) (buffer_33X + 1)) = (unsigned char) ((128 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((258048 & value_32X), 12))));
          *((unsigned char *) (buffer_33X + 2)) = (unsigned char) ((128 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((4032 & value_32X), 6))));
          *((unsigned char *) (buffer_33X + 3)) = (unsigned char) ((128 + (63 & value_32X)));
          *TT0 = 0;
          *TT1 = 4;
          return 1;}}
      else {
        if ((count_34X < 3)) {
          *TT0 = 1;
          *TT1 = 3;
          return 1;}
        else {
          *((unsigned char *) buffer_33X) = (unsigned char) ((224 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((61440 & value_32X), 12))));
          *((unsigned char *) (buffer_33X + 1)) = (unsigned char) ((128 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((4032 & value_32X), 6))));
          *((unsigned char *) (buffer_33X + 2)) = (unsigned char) ((128 + (63 & value_32X)));
          *TT0 = 0;
          *TT1 = 3;
          return 1;}}}
    else {
      if ((count_34X < 2)) {
        *TT0 = 1;
        *TT1 = 2;
        return 1;}
      else {
        *((unsigned char *) buffer_33X) = (unsigned char) ((192 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((1984 & value_32X), 6))));
        *((unsigned char *) (buffer_33X + 1)) = (unsigned char) ((128 + (63 & value_32X)));
        *TT0 = 0;
        *TT1 = 2;
        return 1;}}}
  else {
    if ((count_34X < 1)) {
      *TT0 = 1;
      *TT1 = 1;
      return 1;}
    else {
      *((unsigned char *) buffer_33X) = (unsigned char) (value_32X);
      *TT0 = 0;
      *TT1 = 1;
      return 1;}}}
}
static char decode_scalar_valueUutf_16le(char * buffer_35X, long count_36X, char *TT0, long *TT1, long *TT2)
{
  long word1_38X;
  long word0_37X;
 {  if ((count_36X < 2)) {
    *TT0 = 1;
    *TT1 = 0;
    *TT2 = 2;
    return 1;}
  else {
    word0_37X = (*((unsigned char *) buffer_35X)) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_35X + 1))), 8));
    if ((word0_37X < 55296)) {
      *TT0 = 0;
      *TT1 = word0_37X;
      *TT2 = 2;
      return 1;}
    else {
      if ((57343 < word0_37X)) {
        *TT0 = 0;
        *TT1 = word0_37X;
        *TT2 = 2;
        return 1;}
      else {
        if ((count_36X < 4)) {
          *TT0 = 1;
          *TT1 = 0;
          *TT2 = 4;
          return 1;}
        else {
          if ((56319 < word0_37X)) {
            *TT0 = 0;
            *TT1 = 0;
            *TT2 = 0;
            return 0;}
          else {
            word1_38X = (*((unsigned char *) (buffer_35X + 2))) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_35X + 3))), 8));
            if ((word1_38X < 56320)) {
              *TT0 = 0;
              *TT1 = 0;
              *TT2 = 0;
              return 0;}
            else {
              if ((57343 < word1_38X)) {
                *TT0 = 0;
                *TT1 = 0;
                *TT2 = 0;
                return 0;}
              else {
                *TT0 = 0;
                *TT1 = ((-56557568 + (PS_SHIFT_LEFT_INLINE(word0_37X, 10))) + (1023 & word1_38X));
                *TT2 = 4;
                return 1;}}}}}}}}
}
static char decode_scalar_valueUutf_16be(char * buffer_39X, long count_40X, char *TT0, long *TT1, long *TT2)
{
  long word1_42X;
  long word0_41X;
 {  if ((count_40X < 2)) {
    *TT0 = 1;
    *TT1 = 0;
    *TT2 = 2;
    return 1;}
  else {
    word0_41X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) buffer_39X)), 8)) + (*((unsigned char *) (buffer_39X + 1)));
    if ((word0_41X < 55296)) {
      *TT0 = 0;
      *TT1 = word0_41X;
      *TT2 = 2;
      return 1;}
    else {
      if ((57343 < word0_41X)) {
        *TT0 = 0;
        *TT1 = word0_41X;
        *TT2 = 2;
        return 1;}
      else {
        if ((count_40X < 4)) {
          *TT0 = 1;
          *TT1 = 0;
          *TT2 = 4;
          return 1;}
        else {
          if ((56319 < word0_41X)) {
            *TT0 = 0;
            *TT1 = 0;
            *TT2 = 0;
            return 0;}
          else {
            word1_42X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_39X + 2))), 8)) + (*((unsigned char *) (buffer_39X + 3)));
            if ((word1_42X < 56320)) {
              *TT0 = 0;
              *TT1 = 0;
              *TT2 = 0;
              return 0;}
            else {
              if ((57343 < word1_42X)) {
                *TT0 = 0;
                *TT1 = 0;
                *TT2 = 0;
                return 0;}
              else {
                *TT0 = 0;
                *TT1 = ((-56557568 + (PS_SHIFT_LEFT_INLINE(word0_41X, 10))) + (1023 & word1_42X));
                *TT2 = 4;
                return 1;}}}}}}}}
}
static char decode_scalar_valueUutf_8(char * buffer_43X, long count_44X, char *TT0, long *TT1, long *TT2)
{
  long arg0K3;
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long v_52X;
  long scalar_value_51X;
  long state_50X;
  long c_49X;
  long scalar_value_48X;
  long mask_47X;
  long state_46X;
  long q_45X;
 {  arg0K0 = 0;
  arg0K1 = 0;
  arg0K2 = 0;
  arg0K3 = 0;
  goto L8097;}
 L8097: {
  q_45X = arg0K0;
  state_46X = arg0K1;
  mask_47X = arg0K2;
  scalar_value_48X = arg0K3;
  if ((q_45X < count_44X)) {
    c_49X = *((unsigned char *) (buffer_43X + q_45X));
    state_50X = *(Sutf_8_state_tableS + ((PS_SHIFT_LEFT_INLINE(state_46X, 5)) + (PS_SHIFT_RIGHT_INLINE(c_49X, 3))));
    if ((state_50X == 0)) {
      scalar_value_51X = scalar_value_48X + (127 & c_49X);
      if ((scalar_value_51X < 0)) {
        *TT0 = 0;
        *TT1 = 0;
        *TT2 = 0;
        return 0;}
      else {
        if ((55295 < scalar_value_51X)) {
          if ((scalar_value_51X < 57344)) {
            *TT0 = 0;
            *TT1 = 0;
            *TT2 = 0;
            return 0;}
          else {
            if ((1114111 < scalar_value_51X)) {
              *TT0 = 0;
              *TT1 = 0;
              *TT2 = 0;
              return 0;}
            else {
              goto L8112;}}}
        else {
          goto L8112;}}}
    else {
      if ((state_50X == 1)) {
        goto L8123;}
      else {
        if ((state_50X == 2)) {
          goto L8123;}
        else {
          if ((state_50X == 3)) {
            goto L8123;}
          else {
            if ((state_50X == -2)) {
              *TT0 = 0;
              *TT1 = 0;
              *TT2 = 0;
              return 0;}
            else {
              if ((state_50X == -1)) {
                *TT0 = 0;
                *TT1 = 0;
                *TT2 = 0;
                return 0;}
              else {
                *TT0 = 0;
                *TT1 = 0;
                *TT2 = 0;
                return 0;}}}}}}}
  else {
    *TT0 = 1;
    *TT1 = 0;
    *TT2 = (1 + q_45X);
    return 1;}}
 L8112: {
  *TT0 = 0;
  *TT1 = scalar_value_51X;
  *TT2 = (1 + q_45X);
  return 1;}
 L8123: {
  if ((0 == mask_47X)) {
    arg0K0 = (*(Sutf_8_masksS + state_50X));
    goto L8129;}
  else {
    arg0K0 = mask_47X;
    goto L8129;}}
 L8129: {
  v_52X = arg0K0;
  arg0K0 = (1 + q_45X);
  arg0K1 = state_50X;
  arg0K2 = 63;
  arg0K3 = (PS_SHIFT_LEFT_INLINE((scalar_value_48X + (c_49X & v_52X)), 6));
  goto L8097;}
}
static char integerLE(long x_53X, long y_54X)
{
  long v_57X;
  long v_56X;
  long v_55X;
 {  if ((0 == (3 & y_54X))) {
    if ((0 == (3 & x_53X))) {
      if ((y_54X < x_53X)) {
        return 0;}
      else {
        return 1;}}
    else {
      v_55X = s48_bignum_test((((char *) (-3 + x_53X))));
      if ((1 == v_55X)) {
        return 0;}
      else {
        return 1;}}}
  else {
    if ((0 == (3 & x_53X))) {
      v_56X = s48_bignum_test((((char *) (-3 + y_54X))));
      if ((1 == v_56X)) {
        return 1;}
      else {
        return 0;}}
    else {
      v_57X = s48_bignum_compare((((char *) (-3 + y_54X))), (((char *) (-3 + x_53X))));
      if ((-1 == v_57X)) {
        return 0;}
      else {
        return 1;}}}}
}
static char integerGE(long x_58X, long y_59X)
{
  long v_62X;
  long v_61X;
  long v_60X;
 {  if ((0 == (3 & x_58X))) {
    if ((0 == (3 & y_59X))) {
      if ((x_58X < y_59X)) {
        return 0;}
      else {
        return 1;}}
    else {
      v_60X = s48_bignum_test((((char *) (-3 + y_59X))));
      if ((1 == v_60X)) {
        return 0;}
      else {
        return 1;}}}
  else {
    if ((0 == (3 & y_59X))) {
      v_61X = s48_bignum_test((((char *) (-3 + x_58X))));
      if ((1 == v_61X)) {
        return 1;}
      else {
        return 0;}}
    else {
      v_62X = s48_bignum_compare((((char *) (-3 + x_58X))), (((char *) (-3 + y_59X))));
      if ((-1 == v_62X)) {
        return 0;}
      else {
        return 1;}}}}
}
static char shared_binding_undefinedP(long binding_63X)
{

 {  return (17 == (255 & (*((long *) ((((char *) (-3 + binding_63X))) + 16)))));}
}
static void enqueue_channelB(long index_64X, long status_65X, long errorP_66X)
{
  char * addr_72X;
  long x_71X;
  char * addr_70X;
  char * addr_69X;
  long val_68X;
  long channel_67X;
 {  channel_67X = *((Svm_channelsS) + index_64X);
  val_68X = PS_SHIFT_LEFT_INLINE(status_65X, 2);
  addr_69X = (((char *) (-3 + channel_67X))) + 40;S48_WRITE_BARRIER(channel_67X, addr_69X, val_68X);
  *((long *) addr_69X) = (long) (val_68X);
  addr_70X = (((char *) (-3 + channel_67X))) + 48;S48_WRITE_BARRIER(channel_67X, addr_70X, errorP_66X);
  *((long *) addr_70X) = (long) (errorP_66X);
  if ((1 == (*((long *) ((((char *) (-3 + channel_67X))) + 32))))) {
    if ((channel_67X == (Spending_channels_headS))) {
      return;}
    else {
      if ((channel_67X == (Spending_channels_tailS))) {
        return;}
      else {
        if ((1 == (Spending_channels_headS))) {
          Spending_channels_headS = channel_67X;
          Spending_channels_tailS = channel_67X;
          return;}
        else {
          x_71X = Spending_channels_tailS;
          addr_72X = (((char *) (-3 + x_71X))) + 32;S48_WRITE_BARRIER(x_71X, addr_72X, channel_67X);
          *((long *) addr_72X) = (long) (channel_67X);
          Spending_channels_tailS = channel_67X;
          return;}}}}
  else {
    return;}}
}
static long make_blank_return_code(long protocol_73X, long template_74X, long frame_size_75X, long opcode_count_76X, long key_77X)
{
  long code_80X;
  char * addr_79X;
  long length_78X;
 {  length_78X = 15 + opcode_count_76X;
  addr_79X = s48_allocate_small((8 + length_78X));
  *((long *) addr_79X) = (long) ((70 + (PS_SHIFT_LEFT_INLINE(length_78X, 8))));
  code_80X = 3 + (((long) (addr_79X + 8)));
  *((unsigned char *) (((char *) (-3 + code_80X)))) = (unsigned char) (0);
  *((unsigned char *) ((((char *) (-3 + code_80X))) + 1)) = (unsigned char) (protocol_73X);
  *((unsigned char *) ((((char *) (-3 + code_80X))) + 2)) = (unsigned char) (0);
  *((unsigned char *) ((((char *) (-3 + code_80X))) + 3)) = (unsigned char) (31);
  *((unsigned char *) ((((char *) (-3 + code_80X))) + 4)) = (unsigned char) (0);
  *((unsigned char *) ((((char *) (-3 + code_80X))) + 5)) = (unsigned char) (8);
  *((unsigned char *) ((((char *) (-3 + code_80X))) + 6)) = (unsigned char) ((255 & (PS_SHIFT_RIGHT_INLINE(template_74X, 8))));
  *((unsigned char *) ((((char *) (-3 + code_80X))) + 7)) = (unsigned char) ((255 & template_74X));
  *((unsigned char *) ((((char *) (-3 + code_80X))) + 8)) = (unsigned char) (0);
  *((unsigned char *) ((((char *) (-3 + code_80X))) + 9)) = (unsigned char) (13);
  *((unsigned char *) ((((char *) (-3 + code_80X))) + 10)) = (unsigned char) (0);
  *((unsigned char *) ((((char *) (-3 + code_80X))) + 11)) = (unsigned char) ((255 & (PS_SHIFT_RIGHT_INLINE(frame_size_75X, 8))));
  *((unsigned char *) ((((char *) (-3 + code_80X))) + 12)) = (unsigned char) ((255 & frame_size_75X));
  *((unsigned char *) ((((char *) (-3 + code_80X))) + 13)) = (unsigned char) (0);
  *((unsigned char *) ((((char *) (-3 + code_80X))) + 14)) = (unsigned char) (protocol_73X);
  return code_80X;}
}
static long close_channelB(long channel_81X)
{
  long arg0K0;
  char * addr_89X;
  long status_88X;
  long v_87X;
  long v_86X;
  long v_85X;
  long v_84X;
  long x_83X;
  long os_index_82X;
 {  os_index_82X = PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + channel_81X))) + 16))), 2);
  x_83X = *((long *) ((((char *) (-3 + channel_81X))) + 40));
  if ((5 == x_83X)) {
    v_84X = ps_abort_fd_op(os_index_82X);enqueue_channelB(os_index_82X, v_84X, 1);
    goto L17485;}
  else {
    goto L17485;}}
 L17485: {
  v_85X = *((long *) (((char *) (-3 + channel_81X))));
  if ((4 == v_85X)) {
    goto L17500;}
  else {
    if ((12 == (*((long *) (((char *) (-3 + channel_81X))))))) {
      goto L17500;}
    else {
      v_86X = ps_close_fd(os_index_82X);
      arg0K0 = v_86X;
      goto L17507;}}}
 L17500: {
  v_87X = ps_close_fd(os_index_82X);
  arg0K0 = v_87X;
  goto L17507;}
 L17507: {
  status_88X = arg0K0;
  *((Svm_channelsS) + os_index_82X) = 1;
  addr_89X = ((char *) (-3 + channel_81X));S48_WRITE_BARRIER(channel_81X, addr_89X, 0);
  *((long *) addr_89X) = (long) (0);
  return status_88X;}
}
static void copy_vm_string_to_stringUlatin_1B(long vm_string_90X, long start_91X, long count_92X, char *string_93X)
{
  char arg2K0;
  long arg0K2;
  long arg0K1;
  long arg0K0;
  char v_99X;
  long x_98X;
  long scalar_value_97X;
  long j_96X;
  long bits_95X;
  long i_94X;
 {  arg0K0 = 0;
  goto L18278;}
 L18278: {
  i_94X = arg0K0;
  if ((i_94X < count_92X)) {
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = 0;
    goto L18320;}
  else {
    return;}}
 L18320: {
  bits_95X = arg0K0;
  j_96X = arg0K1;
  scalar_value_97X = arg0K2;
  if ((j_96X < 4)) {
    PS_SHIFT_LEFT((*((unsigned char *) ((((char *) (-3 + vm_string_90X))) + ((PS_SHIFT_LEFT_INLINE(i_94X, 2)) + j_96X)))), bits_95X, x_98X)
    arg0K0 = (8 + bits_95X);
    arg0K1 = (1 + j_96X);
    arg0K2 = (x_98X + scalar_value_97X);
    goto L18320;}
  else {
    if ((255 < scalar_value_97X)) {
      arg2K0 = 63;
      goto L18296;}
    else {
      arg2K0 = (((char) scalar_value_97X));
      goto L18296;}}}
 L18296: {
  v_99X = arg2K0;
  *(string_93X + (i_94X + start_91X)) = v_99X;
  arg0K0 = (1 + i_94X);
  goto L18278;}
}
static void decodeUutf_8B(char * p_100X, long s_101X, long size_102X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long shifted_113X;
  long j_112X;
  long bits_111X;
  long shifted_110X;
  long j_109X;
  long bits_108X;
  long count_107X;
  long value_106X;
  char incompleteP_105X;
  long target_index_104X;
  long index_103X;
 {  arg0K0 = 0;
  arg0K1 = 0;
  goto L19075;}
 L19075: {
  index_103X = arg0K0;
  target_index_104X = arg0K1;
  if ((index_103X < size_102X)) {decode_scalar_valueUutf_8((p_100X + index_103X), (size_102X - index_103X), &incompleteP_105X, &value_106X, &count_107X);
    if (incompleteP_105X) {
      arg0K0 = 0;
      arg0K1 = 0;
      arg0K2 = 63;
      goto L19206;}
    else {
      arg0K0 = 0;
      arg0K1 = 0;
      arg0K2 = value_106X;
      goto L19223;}}
  else {
    return;}}
 L19206: {
  bits_108X = arg0K0;
  j_109X = arg0K1;
  shifted_110X = arg0K2;
  if ((j_109X < 4)) {
    *((unsigned char *) ((((char *) (-3 + s_101X))) + ((PS_SHIFT_LEFT_INLINE(target_index_104X, 2)) + j_109X))) = (unsigned char) ((255 & shifted_110X));
    arg0K0 = (8 + bits_108X);
    arg0K1 = (1 + j_109X);
    arg0K2 = (PS_SHIFT_RIGHT_LOGICAL_INLINE(shifted_110X, 8));
    goto L19206;}
  else {
    return;}}
 L19223: {
  bits_111X = arg0K0;
  j_112X = arg0K1;
  shifted_113X = arg0K2;
  if ((j_112X < 4)) {
    *((unsigned char *) ((((char *) (-3 + s_101X))) + ((PS_SHIFT_LEFT_INLINE(target_index_104X, 2)) + j_112X))) = (unsigned char) ((255 & shifted_113X));
    arg0K0 = (8 + bits_111X);
    arg0K1 = (1 + j_112X);
    arg0K2 = (PS_SHIFT_RIGHT_LOGICAL_INLINE(shifted_113X, 8));
    goto L19223;}
  else {
    arg0K0 = (index_103X + count_107X);
    arg0K1 = (1 + target_index_104X);
    goto L19075;}}
}
static void decodeUutf_16beB(char * p_114X, long s_115X, long size_116X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long shifted_127X;
  long j_126X;
  long bits_125X;
  long shifted_124X;
  long j_123X;
  long bits_122X;
  long count_121X;
  long value_120X;
  char incompleteP_119X;
  long target_index_118X;
  long index_117X;
 {  arg0K0 = 0;
  arg0K1 = 0;
  goto L19274;}
 L19274: {
  index_117X = arg0K0;
  target_index_118X = arg0K1;
  if ((index_117X < size_116X)) {decode_scalar_valueUutf_16be((p_114X + index_117X), (size_116X - index_117X), &incompleteP_119X, &value_120X, &count_121X);
    if (incompleteP_119X) {
      arg0K0 = 0;
      arg0K1 = 0;
      arg0K2 = 63;
      goto L19405;}
    else {
      arg0K0 = 0;
      arg0K1 = 0;
      arg0K2 = value_120X;
      goto L19422;}}
  else {
    return;}}
 L19405: {
  bits_122X = arg0K0;
  j_123X = arg0K1;
  shifted_124X = arg0K2;
  if ((j_123X < 4)) {
    *((unsigned char *) ((((char *) (-3 + s_115X))) + ((PS_SHIFT_LEFT_INLINE(target_index_118X, 2)) + j_123X))) = (unsigned char) ((255 & shifted_124X));
    arg0K0 = (8 + bits_122X);
    arg0K1 = (1 + j_123X);
    arg0K2 = (PS_SHIFT_RIGHT_LOGICAL_INLINE(shifted_124X, 8));
    goto L19405;}
  else {
    return;}}
 L19422: {
  bits_125X = arg0K0;
  j_126X = arg0K1;
  shifted_127X = arg0K2;
  if ((j_126X < 4)) {
    *((unsigned char *) ((((char *) (-3 + s_115X))) + ((PS_SHIFT_LEFT_INLINE(target_index_118X, 2)) + j_126X))) = (unsigned char) ((255 & shifted_127X));
    arg0K0 = (8 + bits_125X);
    arg0K1 = (1 + j_126X);
    arg0K2 = (PS_SHIFT_RIGHT_LOGICAL_INLINE(shifted_127X, 8));
    goto L19422;}
  else {
    arg0K0 = (index_117X + count_121X);
    arg0K1 = (1 + target_index_118X);
    goto L19274;}}
}
static void decodeUutf_16leB(char * p_128X, long s_129X, long size_130X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long shifted_141X;
  long j_140X;
  long bits_139X;
  long shifted_138X;
  long j_137X;
  long bits_136X;
  long count_135X;
  long value_134X;
  char incompleteP_133X;
  long target_index_132X;
  long index_131X;
 {  arg0K0 = 0;
  arg0K1 = 0;
  goto L19473;}
 L19473: {
  index_131X = arg0K0;
  target_index_132X = arg0K1;
  if ((index_131X < size_130X)) {decode_scalar_valueUutf_16le((p_128X + index_131X), (size_130X - index_131X), &incompleteP_133X, &value_134X, &count_135X);
    if (incompleteP_133X) {
      arg0K0 = 0;
      arg0K1 = 0;
      arg0K2 = 63;
      goto L19604;}
    else {
      arg0K0 = 0;
      arg0K1 = 0;
      arg0K2 = value_134X;
      goto L19621;}}
  else {
    return;}}
 L19604: {
  bits_136X = arg0K0;
  j_137X = arg0K1;
  shifted_138X = arg0K2;
  if ((j_137X < 4)) {
    *((unsigned char *) ((((char *) (-3 + s_129X))) + ((PS_SHIFT_LEFT_INLINE(target_index_132X, 2)) + j_137X))) = (unsigned char) ((255 & shifted_138X));
    arg0K0 = (8 + bits_136X);
    arg0K1 = (1 + j_137X);
    arg0K2 = (PS_SHIFT_RIGHT_LOGICAL_INLINE(shifted_138X, 8));
    goto L19604;}
  else {
    return;}}
 L19621: {
  bits_139X = arg0K0;
  j_140X = arg0K1;
  shifted_141X = arg0K2;
  if ((j_140X < 4)) {
    *((unsigned char *) ((((char *) (-3 + s_129X))) + ((PS_SHIFT_LEFT_INLINE(target_index_132X, 2)) + j_140X))) = (unsigned char) ((255 & shifted_141X));
    arg0K0 = (8 + bits_139X);
    arg0K1 = (1 + j_140X);
    arg0K2 = (PS_SHIFT_RIGHT_LOGICAL_INLINE(shifted_141X, 8));
    goto L19621;}
  else {
    arg0K0 = (index_131X + count_135X);
    arg0K1 = (1 + target_index_132X);
    goto L19473;}}
}
static char not_record_typeP(long thing_142X)
{
  long obj_143X;
 {  if ((3 == (3 & thing_142X))) {
    if ((9 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + thing_142X))))), 2))))) {
      obj_143X = *((long *) ((((char *) (-3 + thing_142X))) + 24));
      if ((3 == (3 & obj_143X))) {
        if ((1 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_143X))))), 2))))) {
          return ((PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + thing_142X))))), 8))), 3)) < 12);}
        else {
          return 1;}}
      else {
        return 1;}}
    else {
      return 1;}}
  else {
    return 1;}}
}
static long enter_bignum(char * external_bignum_144X)
{
  long desc_145X;
 {  desc_145X = 3 + (((long) external_bignum_144X));
  if ((3 == (3 & desc_145X))) {
    if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + desc_145X))))), 2))))) {
      goto L20321;}
    else {
      goto L20335;}}
  else {
    goto L20335;}}
 L20321: {
  if ((3 == (3 & desc_145X))) {
    if ((0 == (128 & (*((long *) (((char *) (-11 + desc_145X)))))))) {
      *((long *) (((char *) (-11 + desc_145X)))) = (long) ((128 | (*((long *) (((char *) (-11 + desc_145X)))))));
      return desc_145X;}
    else {
      return desc_145X;}}
  else {
    return desc_145X;}}
 L20335: {
  ps_error("not a bignum", 1, desc_145X);
  goto L20321;}
}
static char integerE(long x_146X, long y_147X)
{

 {  if ((0 == (3 & (x_146X | y_147X)))) {
    return (x_146X == y_147X);}
  else {
    if ((3 == (3 & x_146X))) {
      if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + x_146X))))), 2))))) {
        if ((3 == (3 & y_147X))) {
          if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_147X))))), 2))))) {
            return s48_bignum_equal_p((((char *) (-3 + x_146X))), (((char *) (-3 + y_147X))));}
          else {
            return 0;}}
        else {
          return 0;}}
      else {
        return 0;}}
    else {
      return 0;}}}
}
static long add_log_entryAgc(long proposal_index_148X, long i_149X, long stob_150X, long index_151X, long value_152X, char verifyP_153X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  char * addr_178X;
  long value_177X;
  long v_176X;
  long value_175X;
  char * addr_174X;
  long i_173X;
  long stob_172X;
  long proposal_171X;
  long new_170X;
  char * addr_169X;
  char * addr_168X;
  long value_167X;
  long vector_166X;
  char * addr_165X;
  char * addr_164X;
  char * addr_163X;
  long log_162X;
  long value_161X;
  long stob_160X;
  long proposal_159X;
  char * addr_158X;
  long len_in_bytes_157X;
  long new_size_156X;
  long log_size_155X;
  long proposal_154X;
 {  proposal_154X = *((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24));
  log_size_155X = PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + (*((long *) ((((char *) (-3 + proposal_154X))) + (PS_SHIFT_LEFT_INLINE(proposal_index_148X, 3)))))))))), 8))), 3);
  if ((i_149X == (-1 + log_size_155X))) {
    Stemp0S = stob_150X;
    Stemp1S = value_152X;
    if ((1 == log_size_155X)) {
      arg0K0 = 17;
      goto L16300;}
    else {
      arg0K0 = (-1 + (PS_SHIFT_LEFT_INLINE(log_size_155X, 1)));
      goto L16300;}}
  else {
    arg0K0 = proposal_154X;
    arg0K1 = stob_150X;
    arg0K2 = value_152X;
    goto L21592;}}
 L16300: {
  new_size_156X = arg0K0;
  len_in_bytes_157X = PS_SHIFT_LEFT_INLINE(new_size_156X, 3);
  addr_158X = s48_allocate_tracedAgc((8 + len_in_bytes_157X));
  if ((addr_158X == NULL)) {
    arg0K0 = 1;
    goto L16346;}
  else {
    *((long *) addr_158X) = (long) ((10 + (PS_SHIFT_LEFT_INLINE(len_in_bytes_157X, 8))));
    arg0K0 = (3 + (((long) (addr_158X + 8))));
    goto L16346;}}
 L21592: {
  proposal_159X = arg0K0;
  stob_160X = arg0K1;
  value_161X = arg0K2;
  log_162X = *((long *) ((((char *) (-3 + proposal_159X))) + (PS_SHIFT_LEFT_INLINE(proposal_index_148X, 3))));
  addr_163X = (((char *) (-3 + log_162X))) + (PS_SHIFT_LEFT_INLINE(i_149X, 3));S48_WRITE_BARRIER(log_162X, addr_163X, stob_160X);
  *((long *) addr_163X) = (long) (stob_160X);
  addr_164X = (((char *) (-3 + log_162X))) + (8 + (PS_SHIFT_LEFT_INLINE(i_149X, 3)));S48_WRITE_BARRIER(log_162X, addr_164X, index_151X);
  *((long *) addr_164X) = (long) (index_151X);
  addr_165X = (((char *) (-3 + log_162X))) + (16 + (PS_SHIFT_LEFT_INLINE(i_149X, 3)));S48_WRITE_BARRIER(log_162X, addr_165X, value_161X);
  *((long *) addr_165X) = (long) (value_161X);
  if (verifyP_153X) {
    arg0K0 = value_161X;
    goto L21613;}
  else {
    arg0K0 = 29;
    goto L21613;}}
 L16346: {
  vector_166X = arg0K0;
  if ((1 == vector_166X)) {
    ps_error("Out of space, unable to allocate", 0);
    arg0K0 = vector_166X;
    goto L16304;}
  else {
    arg0K0 = vector_166X;
    goto L16304;}}
 L21613: {
  value_167X = arg0K0;
  addr_168X = (((char *) (-3 + log_162X))) + (24 + (PS_SHIFT_LEFT_INLINE(i_149X, 3)));S48_WRITE_BARRIER(log_162X, addr_168X, value_167X);
  *((long *) addr_168X) = (long) (value_167X);
  addr_169X = (((char *) (-3 + log_162X))) + (32 + (PS_SHIFT_LEFT_INLINE(i_149X, 3)));S48_WRITE_BARRIER(log_162X, addr_169X, 1);
  *((long *) addr_169X) = (long) (1);
  return value_161X;}
 L16304: {
  new_170X = arg0K0;
  proposal_171X = *((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24));
  if ((1 < log_size_155X)) {
    stob_172X = *((long *) ((((char *) (-3 + proposal_171X))) + 8));
    memmove((void *)(((char *) (-3 + new_170X))), (void *)(((char *) (-3 + stob_172X))),(-8 + (PS_SHIFT_LEFT_INLINE(log_size_155X, 3))));
    goto L16324;}
  else {
    goto L16324;}}
 L16324: {
  arg0K0 = (4 + log_size_155X);
  goto L16328;}
 L16328: {
  i_173X = arg0K0;
  if ((i_173X == new_size_156X)) {
    addr_174X = (((char *) (-3 + proposal_171X))) + (PS_SHIFT_LEFT_INLINE(proposal_index_148X, 3));S48_WRITE_BARRIER(proposal_171X, addr_174X, new_170X);
    *((long *) addr_174X) = (long) (new_170X);
    value_175X = Stemp0S;
    Stemp0S = 1;
    v_176X = *((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24));
    value_177X = Stemp1S;
    Stemp1S = 1;
    arg0K0 = v_176X;
    arg0K1 = value_175X;
    arg0K2 = value_177X;
    goto L21592;}
  else {
    addr_178X = (((char *) (-3 + new_170X))) + (PS_SHIFT_LEFT_INLINE(i_173X, 3));S48_WRITE_BARRIER(new_170X, addr_178X, 0);
    *((long *) addr_178X) = (long) (0);
    arg0K0 = (1 + i_173X);
    goto L16328;}}
}
static long make_channel(long a_179X, long b_180X, long c_181X, long d_182X, long e_183X, long f_184X, long g_185X, long key_186X)
{
  long x_188X;
  char * addr_187X;
 {  addr_187X = s48_allocate_small(64);
  *((long *) addr_187X) = (long) (14362);
  x_188X = 3 + (((long) (addr_187X + 8)));
  *((long *) (((char *) (-3 + x_188X)))) = (long) (a_179X);
  *((long *) ((((char *) (-3 + x_188X))) + 8)) = (long) (b_180X);
  *((long *) ((((char *) (-3 + x_188X))) + 16)) = (long) (c_181X);
  *((long *) ((((char *) (-3 + x_188X))) + 24)) = (long) (d_182X);
  *((long *) ((((char *) (-3 + x_188X))) + 32)) = (long) (e_183X);
  *((long *) ((((char *) (-3 + x_188X))) + 40)) = (long) (f_184X);
  *((long *) ((((char *) (-3 + x_188X))) + 48)) = (long) (g_185X);
  return x_188X;}
}
static long enter_stringAgc_n(char *string_189X, long len_190X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long shifted_199X;
  long j_198X;
  long bits_197X;
  long c_196X;
  long i_195X;
  long s_194X;
  long string_193X;
  char * addr_192X;
  long len_191X;
 {  len_191X = PS_SHIFT_LEFT_INLINE(len_190X, 2);
  addr_192X = s48_allocate_untracedAgc((8 + len_191X));
  if ((addr_192X == NULL)) {
    arg0K0 = 1;
    goto L22341;}
  else {
    *((long *) addr_192X) = (long) ((66 + (PS_SHIFT_LEFT_INLINE(len_191X, 8))));
    arg0K0 = (3 + (((long) (addr_192X + 8))));
    goto L22341;}}
 L22341: {
  string_193X = arg0K0;
  if ((1 == string_193X)) {
    ps_error("Out of space, unable to allocate", 0);
    arg0K0 = string_193X;
    goto L22332;}
  else {
    arg0K0 = string_193X;
    goto L22332;}}
 L22332: {
  s_194X = arg0K0;
  arg0K0 = 0;
  goto L22364;}
 L22364: {
  i_195X = arg0K0;
  if ((i_195X < len_190X)) {
    c_196X = ((unsigned char) (*(string_189X + i_195X)));
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = c_196X;
    goto L22375;}
  else {
    return s_194X;}}
 L22375: {
  bits_197X = arg0K0;
  j_198X = arg0K1;
  shifted_199X = arg0K2;
  if ((j_198X < 4)) {
    *((unsigned char *) ((((char *) (-3 + s_194X))) + ((PS_SHIFT_LEFT_INLINE(i_195X, 2)) + j_198X))) = (unsigned char) ((255 & shifted_199X));
    arg0K0 = (8 + bits_197X);
    arg0K1 = (1 + j_198X);
    arg0K2 = (PS_SHIFT_RIGHT_LOGICAL_INLINE(shifted_199X, 8));
    goto L22375;}
  else {
    arg0K0 = (1 + i_195X);
    goto L22364;}}
}
static long write_vm_string(long vm_string_200X, FILE * out_201X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long x_208X;
  long scalar_value_207X;
  long j_206X;
  long bits_205X;
  long i_204X;
  long size_203X;
  long v_202X;
 {  v_202X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_200X))))), 8)) / 4;
  arg0K0 = v_202X;
  arg0K1 = 0;
  goto L22811;}
 L22811: {
  size_203X = arg0K0;
  i_204X = arg0K1;
  if ((i_204X < size_203X)) {
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = 0;
    goto L22844;}
  else {
    return 0;}}
 L22844: {
  bits_205X = arg0K0;
  j_206X = arg0K1;
  scalar_value_207X = arg0K2;
  if ((j_206X < 4)) {
    PS_SHIFT_LEFT((*((unsigned char *) ((((char *) (-3 + vm_string_200X))) + ((PS_SHIFT_LEFT_INLINE(i_204X, 2)) + j_206X)))), bits_205X, x_208X)
    arg0K0 = (8 + bits_205X);
    arg0K1 = (1 + j_206X);
    arg0K2 = (x_208X + scalar_value_207X);
    goto L22844;}
  else {
    { long ignoreXX;
    PS_WRITE_CHAR((((char) scalar_value_207X)), out_201X, ignoreXX) }
    arg0K0 = size_203X;
    arg0K1 = (1 + i_204X);
    goto L22811;}}
}
static long Haction5350(long s_209X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long x_216X;
  long scalar_value_215X;
  long j_214X;
  long bits_213X;
  long ans_212X;
  long i_211X;
  long end_210X;
 {  end_210X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + s_209X))))), 8)) / 4;
  arg0K0 = 0;
  arg0K1 = 0;
  goto L22942;}
 L22942: {
  i_211X = arg0K0;
  ans_212X = arg0K1;
  if ((i_211X < end_210X)) {
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = 0;
    goto L22971;}
  else {
    return (ans_212X % 72057594037927936);}}
 L22971: {
  bits_213X = arg0K0;
  j_214X = arg0K1;
  scalar_value_215X = arg0K2;
  if ((j_214X < 4)) {
    PS_SHIFT_LEFT((*((unsigned char *) ((((char *) (-3 + s_209X))) + ((PS_SHIFT_LEFT_INLINE(i_211X, 2)) + j_214X)))), bits_213X, x_216X)
    arg0K0 = (8 + bits_213X);
    arg0K1 = (1 + j_214X);
    arg0K2 = (x_216X + scalar_value_215X);
    goto L22971;}
  else {
    arg0K0 = (1 + i_211X);
    arg0K1 = (72057594037927935 & ((37 * ans_212X) + scalar_value_215X));
    goto L22942;}}
}
static long current_code_vector(void)
{
  long arg0K0;
  long x_229X;
  long v_228X;
  long x_227X;
  long header_226X;
  char * start_225X;
  char * code_pointer_224X;
  long code_223X;
  char * pointer_222X;
  char * code_pointer_221X;
  long header_220X;
  char * start_219X;
  long code_218X;
  char * code_pointer_217X;
 {  code_pointer_217X = Scode_pointerS;
  code_218X = Slast_code_calledS;
  start_219X = ((char *) (-3 + code_218X));
  if ((code_pointer_217X < start_219X)) {
    goto L23520;}
  else {
    header_220X = *((long *) (((char *) (-11 + code_218X))));
    if ((3 == (3 & header_220X))) {
      arg0K0 = header_220X;
      goto L23541;}
    else {
      arg0K0 = code_218X;
      goto L23541;}}}
 L23520: {
  code_pointer_221X = Slast_code_pointer_resumedS;
  pointer_222X = code_pointer_221X + -5;
  code_223X = 3 + (((long) (code_pointer_221X + (0 - ((PS_SHIFT_LEFT_INLINE((*((unsigned char *) pointer_222X)), 8)) + (*((unsigned char *) (pointer_222X + 1))))))));
  code_pointer_224X = Scode_pointerS;
  start_225X = ((char *) (-3 + code_223X));
  if ((code_pointer_224X < start_225X)) {
    goto L23528;}
  else {
    header_226X = *((long *) (((char *) (-11 + code_223X))));
    if ((3 == (3 & header_226X))) {
      arg0K0 = header_226X;
      goto L23562;}
    else {
      arg0K0 = code_223X;
      goto L23562;}}}
 L23541: {
  x_227X = arg0K0;
  if ((code_pointer_217X < (start_219X + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + x_227X))))), 8))))) {
    return (Slast_code_calledS);}
  else {
    goto L23520;}}
 L23528: {
  ps_error("VM error: unable to locate current code vector", 3, (((long) (Scode_pointerS))), (Slast_code_calledS), (((long) (Slast_code_pointer_resumedS))));
  return v_228X;}
 L23562: {
  x_229X = arg0K0;
  if ((code_pointer_224X < (start_225X + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + x_229X))))), 8))))) {
    return code_223X;}
  else {
    goto L23528;}}
}
static void channel_close_error(long status_230X, long index_231X, long id_232X)
{

 {  ps_write_string("Error: ", (stderr));
  ps_write_string((ps_error_string(status_230X)), (stderr));
  { long ignoreXX;
  PS_WRITE_CHAR(10, (stderr), ignoreXX) }
  ps_write_string(" while closing port ", (stderr));
  if ((3 == (3 & id_232X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + id_232X))))), 2))))) {
      ps_write_string((((char *)(((char *) (-3 + id_232X))))), (stderr));
      goto L23990;}
    else {
      goto L23978;}}
  else {
    goto L23978;}}
 L23990: {
  { long ignoreXX;
  PS_WRITE_CHAR(10, (stderr), ignoreXX) }
  return;}
 L23978: {
  if ((0 == (3 & id_232X))) {
    ps_write_integer((PS_SHIFT_RIGHT_INLINE(index_231X, 2)), (stderr));
    goto L23990;}
  else {
    ps_write_string("<strange id>", (stderr));
    goto L23990;}}
}
static long integer_bit_count(long x_233X)
{
  long arg0K1;
  long arg0K0;
  char * arg3K0;
  long n_240X;
  char * v_239X;
  char * v_238X;
  long value_237X;
  long v_236X;
  long extra_235X;
  long length_234X;
 {  if ((0 == (3 & x_233X))) {
    arg0K0 = 1;
    arg0K1 = 3;
    goto L26177;}
  else {
    arg0K0 = (-1 + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + x_233X))))), 8))), 3)));
    arg0K1 = 0;
    goto L26177;}}
 L26177: {
  length_234X = arg0K0;
  extra_235X = arg0K1;
  if ((length_234X < 1)) {
    arg0K0 = 1;
    goto L26179;}
  else {
    arg0K0 = length_234X;
    goto L26179;}}
 L26179: {
  v_236X = arg0K0;
  Stemp0S = x_233X;s48_make_availableAgc((PS_SHIFT_LEFT_INLINE(((1 + (PS_SHIFT_RIGHT_INLINE((23 + (PS_SHIFT_LEFT_INLINE(v_236X, 3))), 3))) + extra_235X), 3)));
  value_237X = Stemp0S;
  Stemp0S = 1;
  if ((0 == (3 & value_237X))) {
    v_238X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_237X, 2)));
    arg3K0 = v_238X;
    goto L26169;}
  else {
    arg3K0 = (((char *) (-3 + value_237X)));
    goto L26169;}}
 L26169: {
  v_239X = arg3K0;
  n_240X = s48_bignum_bit_count(v_239X);
  return (PS_SHIFT_LEFT_INLINE(n_240X, 2));}
}
static long integer_add(long x_241X, long y_242X)
{
  char * arg3K0;
  long arg0K1;
  long arg0K0;
  long n_256X;
  char v_255X;
  char * external_bignum_254X;
  char * y_253X;
  char * v_252X;
  long value_251X;
  char * x_250X;
  char * v_249X;
  long value_248X;
  long v_247X;
  long extra1_246X;
  long length1_245X;
  long extra0_244X;
  long length0_243X;
 {  if ((0 == (3 & x_241X))) {
    arg0K0 = 1;
    arg0K1 = 3;
    goto L23479;}
  else {
    arg0K0 = (-1 + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + x_241X))))), 8))), 3)));
    arg0K1 = 0;
    goto L23479;}}
 L23479: {
  length0_243X = arg0K0;
  extra0_244X = arg0K1;
  if ((0 == (3 & y_242X))) {
    arg0K0 = 1;
    arg0K1 = 3;
    goto L23487;}
  else {
    arg0K0 = (-1 + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + y_242X))))), 8))), 3)));
    arg0K1 = 0;
    goto L23487;}}
 L23487: {
  length1_245X = arg0K0;
  extra1_246X = arg0K1;
  if ((length0_243X < length1_245X)) {
    arg0K0 = length1_245X;
    goto L23509;}
  else {
    arg0K0 = length0_243X;
    goto L23509;}}
 L23509: {
  v_247X = arg0K0;
  Stemp0S = x_241X;
  Stemp1S = y_242X;s48_make_availableAgc((PS_SHIFT_LEFT_INLINE((((1 + (PS_SHIFT_RIGHT_INLINE((23 + (PS_SHIFT_LEFT_INLINE(v_247X, 3))), 3))) + extra0_244X) + extra1_246X), 3)));
  value_248X = Stemp0S;
  Stemp0S = 1;
  if ((0 == (3 & value_248X))) {
    v_249X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_248X, 2)));
    arg3K0 = v_249X;
    goto L26317;}
  else {
    arg3K0 = (((char *) (-3 + value_248X)));
    goto L26317;}}
 L26317: {
  x_250X = arg3K0;
  value_251X = Stemp1S;
  Stemp1S = 1;
  if ((0 == (3 & value_251X))) {
    v_252X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_251X, 2)));
    arg3K0 = v_252X;
    goto L26321;}
  else {
    arg3K0 = (((char *) (-3 + value_251X)));
    goto L26321;}}
 L26321: {
  y_253X = arg3K0;
  external_bignum_254X = (char *)s48_bignum_add(x_250X, y_253X);
  v_255X = s48_bignum_fits_in_word_p(external_bignum_254X, 62, 1);
  if (v_255X) {
    n_256X = s48_bignum_to_long(external_bignum_254X);
    return (PS_SHIFT_LEFT_INLINE(n_256X, 2));}
  else {
    return enter_bignum(external_bignum_254X);}}
}
static long integer_subtract(long x_257X, long y_258X)
{
  char * arg3K0;
  long arg0K1;
  long arg0K0;
  long n_272X;
  char v_271X;
  char * external_bignum_270X;
  char * y_269X;
  char * v_268X;
  long value_267X;
  char * x_266X;
  char * v_265X;
  long value_264X;
  long v_263X;
  long extra1_262X;
  long length1_261X;
  long extra0_260X;
  long length0_259X;
 {  if ((0 == (3 & x_257X))) {
    arg0K0 = 1;
    arg0K1 = 3;
    goto L23436;}
  else {
    arg0K0 = (-1 + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + x_257X))))), 8))), 3)));
    arg0K1 = 0;
    goto L23436;}}
 L23436: {
  length0_259X = arg0K0;
  extra0_260X = arg0K1;
  if ((0 == (3 & y_258X))) {
    arg0K0 = 1;
    arg0K1 = 3;
    goto L23444;}
  else {
    arg0K0 = (-1 + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + y_258X))))), 8))), 3)));
    arg0K1 = 0;
    goto L23444;}}
 L23444: {
  length1_261X = arg0K0;
  extra1_262X = arg0K1;
  if ((length0_259X < length1_261X)) {
    arg0K0 = length1_261X;
    goto L23466;}
  else {
    arg0K0 = length0_259X;
    goto L23466;}}
 L23466: {
  v_263X = arg0K0;
  Stemp0S = x_257X;
  Stemp1S = y_258X;s48_make_availableAgc((PS_SHIFT_LEFT_INLINE((((1 + (PS_SHIFT_RIGHT_INLINE((23 + (PS_SHIFT_LEFT_INLINE(v_263X, 3))), 3))) + extra0_260X) + extra1_262X), 3)));
  value_264X = Stemp0S;
  Stemp0S = 1;
  if ((0 == (3 & value_264X))) {
    v_265X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_264X, 2)));
    arg3K0 = v_265X;
    goto L26391;}
  else {
    arg3K0 = (((char *) (-3 + value_264X)));
    goto L26391;}}
 L26391: {
  x_266X = arg3K0;
  value_267X = Stemp1S;
  Stemp1S = 1;
  if ((0 == (3 & value_267X))) {
    v_268X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_267X, 2)));
    arg3K0 = v_268X;
    goto L26395;}
  else {
    arg3K0 = (((char *) (-3 + value_267X)));
    goto L26395;}}
 L26395: {
  y_269X = arg3K0;
  external_bignum_270X = (char *)s48_bignum_subtract(x_266X, y_269X);
  v_271X = s48_bignum_fits_in_word_p(external_bignum_270X, 62, 1);
  if (v_271X) {
    n_272X = s48_bignum_to_long(external_bignum_270X);
    return (PS_SHIFT_LEFT_INLINE(n_272X, 2));}
  else {
    return enter_bignum(external_bignum_270X);}}
}
static long integer_multiply(long x_273X, long y_274X)
{
  char * arg3K0;
  long arg0K1;
  long arg0K0;
  long n_287X;
  char v_286X;
  char * external_bignum_285X;
  char * y_284X;
  char * v_283X;
  long value_282X;
  char * x_281X;
  char * v_280X;
  long value_279X;
  long extra1_278X;
  long length1_277X;
  long extra0_276X;
  long length0_275X;
 {  if ((0 == (3 & x_273X))) {
    arg0K0 = 1;
    arg0K1 = 3;
    goto L23399;}
  else {
    arg0K0 = (-1 + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + x_273X))))), 8))), 3)));
    arg0K1 = 0;
    goto L23399;}}
 L23399: {
  length0_275X = arg0K0;
  extra0_276X = arg0K1;
  if ((0 == (3 & y_274X))) {
    arg0K0 = 1;
    arg0K1 = 3;
    goto L23407;}
  else {
    arg0K0 = (-1 + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + y_274X))))), 8))), 3)));
    arg0K1 = 0;
    goto L23407;}}
 L23407: {
  length1_277X = arg0K0;
  extra1_278X = arg0K1;
  Stemp0S = x_273X;
  Stemp1S = y_274X;s48_make_availableAgc((PS_SHIFT_LEFT_INLINE((((1 + (PS_SHIFT_RIGHT_INLINE((15 + (PS_SHIFT_LEFT_INLINE((length0_275X + length1_277X), 3))), 3))) + extra0_276X) + extra1_278X), 3)));
  value_279X = Stemp0S;
  Stemp0S = 1;
  if ((0 == (3 & value_279X))) {
    v_280X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_279X, 2)));
    arg3K0 = v_280X;
    goto L26465;}
  else {
    arg3K0 = (((char *) (-3 + value_279X)));
    goto L26465;}}
 L26465: {
  x_281X = arg3K0;
  value_282X = Stemp1S;
  Stemp1S = 1;
  if ((0 == (3 & value_282X))) {
    v_283X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_282X, 2)));
    arg3K0 = v_283X;
    goto L26469;}
  else {
    arg3K0 = (((char *) (-3 + value_282X)));
    goto L26469;}}
 L26469: {
  y_284X = arg3K0;
  external_bignum_285X = (char *)s48_bignum_multiply(x_281X, y_284X);
  v_286X = s48_bignum_fits_in_word_p(external_bignum_285X, 62, 1);
  if (v_286X) {
    n_287X = s48_bignum_to_long(external_bignum_285X);
    return (PS_SHIFT_LEFT_INLINE(n_287X, 2));}
  else {
    return enter_bignum(external_bignum_285X);}}
}
static char integer_divide(long x_288X, long y_289X, long *TT0, long *TT1, long *TT2, long *TT3)
{
  char * arg3K0;
  long arg0K1;
  long arg0K0;
  long v_323X;
  long n_322X;
  char v_321X;
  long v_320X;
  long v_319X;
  long n_318X;
  char v_317X;
  long v_316X;
  long v_315X;
  long n_314X;
  char v_313X;
  long v_312X;
  long v_311X;
  long n_310X;
  char v_309X;
  long v_308X;
  long v_307X;
  long n_306X;
  char v_305X;
  long v_304X;
  long n_303X;
  char v_302X;
  char * rem_301X;
  char * quot_300X;
  char div_by_zeroP_299X;
  char * y_298X;
  char * v_297X;
  long value_296X;
  char * x_295X;
  char * v_294X;
  long value_293X;
  long extra1_292X;
  long extra0_291X;
  long length0_290X;
 {  if ((0 == (3 & x_288X))) {
    arg0K0 = 1;
    arg0K1 = 3;
    goto L23004;}
  else {
    arg0K0 = (-1 + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + x_288X))))), 8))), 3)));
    arg0K1 = 0;
    goto L23004;}}
 L23004: {
  length0_290X = arg0K0;
  extra0_291X = arg0K1;
  if ((0 == (3 & y_289X))) {
    arg0K0 = 3;
    goto L23012;}
  else {
    arg0K0 = 0;
    goto L23012;}}
 L23012: {
  extra1_292X = arg0K0;
  Stemp0S = x_288X;
  Stemp1S = y_289X;s48_make_availableAgc((PS_SHIFT_LEFT_INLINE((((6 + (-2 & (PS_SHIFT_RIGHT_INLINE((15 + (PS_SHIFT_LEFT_INLINE(length0_290X, 3))), 2)))) + extra0_291X) + extra1_292X), 3)));
  value_293X = Stemp0S;
  Stemp0S = 1;
  if ((0 == (3 & value_293X))) {
    v_294X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_293X, 2)));
    arg3K0 = v_294X;
    goto L26541;}
  else {
    arg3K0 = (((char *) (-3 + value_293X)));
    goto L26541;}}
 L26541: {
  x_295X = arg3K0;
  value_296X = Stemp1S;
  Stemp1S = 1;
  if ((0 == (3 & value_296X))) {
    v_297X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_296X, 2)));
    arg3K0 = v_297X;
    goto L26545;}
  else {
    arg3K0 = (((char *) (-3 + value_296X)));
    goto L26545;}}
 L26545: {
  y_298X = arg3K0;
  div_by_zeroP_299X = s48_bignum_divide(x_295X, y_298X, &quot_300X, &rem_301X);
  if (div_by_zeroP_299X) {
    v_302X = s48_bignum_fits_in_word_p(y_298X, 62, 1);
    if (v_302X) {
      n_303X = s48_bignum_to_long(y_298X);
      arg0K0 = (PS_SHIFT_LEFT_INLINE(n_303X, 2));
      goto L26567;}
    else {
      v_304X = enter_bignum(y_298X);
      arg0K0 = v_304X;
      goto L26567;}}
  else {
    v_305X = s48_bignum_fits_in_word_p(y_298X, 62, 1);
    if (v_305X) {
      n_306X = s48_bignum_to_long(y_298X);
      arg0K0 = (PS_SHIFT_LEFT_INLINE(n_306X, 2));
      goto L26576;}
    else {
      v_307X = enter_bignum(y_298X);
      arg0K0 = v_307X;
      goto L26576;}}}
 L26567: {
  v_308X = arg0K0;
  v_309X = s48_bignum_fits_in_word_p(x_295X, 62, 1);
  if (v_309X) {
    n_310X = s48_bignum_to_long(x_295X);
    *TT0 = 0;
    *TT1 = 0;
    *TT2 = (PS_SHIFT_LEFT_INLINE(n_310X, 2));
    *TT3 = v_308X;
    return 1;}
  else {
    v_311X = enter_bignum(x_295X);
    *TT0 = 0;
    *TT1 = 0;
    *TT2 = v_311X;
    *TT3 = v_308X;
    return 1;}}
 L26576: {
  v_312X = arg0K0;
  v_313X = s48_bignum_fits_in_word_p(rem_301X, 62, 1);
  if (v_313X) {
    n_314X = s48_bignum_to_long(rem_301X);
    arg0K0 = (PS_SHIFT_LEFT_INLINE(n_314X, 2));
    goto L26572;}
  else {
    v_315X = enter_bignum(rem_301X);
    arg0K0 = v_315X;
    goto L26572;}}
 L26572: {
  v_316X = arg0K0;
  v_317X = s48_bignum_fits_in_word_p(quot_300X, 62, 1);
  if (v_317X) {
    n_318X = s48_bignum_to_long(quot_300X);
    arg0K0 = (PS_SHIFT_LEFT_INLINE(n_318X, 2));
    goto L26570;}
  else {
    v_319X = enter_bignum(quot_300X);
    arg0K0 = v_319X;
    goto L26570;}}
 L26570: {
  v_320X = arg0K0;
  v_321X = s48_bignum_fits_in_word_p(x_295X, 62, 1);
  if (v_321X) {
    n_322X = s48_bignum_to_long(x_295X);
    *TT0 = v_320X;
    *TT1 = v_316X;
    *TT2 = (PS_SHIFT_LEFT_INLINE(n_322X, 2));
    *TT3 = v_312X;
    return 0;}
  else {
    v_323X = enter_bignum(x_295X);
    *TT0 = v_320X;
    *TT1 = v_316X;
    *TT2 = v_323X;
    *TT3 = v_312X;
    return 0;}}
}
static long integer_bitwise_not(long x_324X)
{
  long arg0K1;
  long arg0K0;
  char * arg3K0;
  long n_333X;
  char v_332X;
  char * external_bignum_331X;
  char * v_330X;
  char * v_329X;
  long value_328X;
  long v_327X;
  long extra_326X;
  long length_325X;
 {  if ((0 == (3 & x_324X))) {
    arg0K0 = 1;
    arg0K1 = 3;
    goto L26838;}
  else {
    arg0K0 = (-1 + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + x_324X))))), 8))), 3)));
    arg0K1 = 0;
    goto L26838;}}
 L26838: {
  length_325X = arg0K0;
  extra_326X = arg0K1;
  if ((length_325X < 1)) {
    arg0K0 = 1;
    goto L26840;}
  else {
    arg0K0 = length_325X;
    goto L26840;}}
 L26840: {
  v_327X = arg0K0;
  Stemp0S = x_324X;s48_make_availableAgc((PS_SHIFT_LEFT_INLINE(((1 + (PS_SHIFT_RIGHT_INLINE((23 + (PS_SHIFT_LEFT_INLINE(v_327X, 3))), 3))) + extra_326X), 3)));
  value_328X = Stemp0S;
  Stemp0S = 1;
  if ((0 == (3 & value_328X))) {
    v_329X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_328X, 2)));
    arg3K0 = v_329X;
    goto L26830;}
  else {
    arg3K0 = (((char *) (-3 + value_328X)));
    goto L26830;}}
 L26830: {
  v_330X = arg3K0;
  external_bignum_331X = (char *) s48_bignum_bitwise_not(v_330X);
  v_332X = s48_bignum_fits_in_word_p(external_bignum_331X, 62, 1);
  if (v_332X) {
    n_333X = s48_bignum_to_long(external_bignum_331X);
    return (PS_SHIFT_LEFT_INLINE(n_333X, 2));}
  else {
    return enter_bignum(external_bignum_331X);}}
}
static long integer_bitwise_and(long x_334X, long y_335X)
{
  char * arg3K0;
  long arg0K1;
  long arg0K0;
  long n_349X;
  char v_348X;
  char * external_bignum_347X;
  char * y_346X;
  char * v_345X;
  long value_344X;
  char * x_343X;
  char * v_342X;
  long value_341X;
  long v_340X;
  long extra1_339X;
  long length1_338X;
  long extra0_337X;
  long length0_336X;
 {  if ((0 == (3 & x_334X))) {
    arg0K0 = 1;
    arg0K1 = 3;
    goto L23218;}
  else {
    arg0K0 = (-1 + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + x_334X))))), 8))), 3)));
    arg0K1 = 0;
    goto L23218;}}
 L23218: {
  length0_336X = arg0K0;
  extra0_337X = arg0K1;
  if ((0 == (3 & y_335X))) {
    arg0K0 = 1;
    arg0K1 = 3;
    goto L23226;}
  else {
    arg0K0 = (-1 + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + y_335X))))), 8))), 3)));
    arg0K1 = 0;
    goto L23226;}}
 L23226: {
  length1_338X = arg0K0;
  extra1_339X = arg0K1;
  if ((length0_336X < length1_338X)) {
    arg0K0 = length1_338X;
    goto L23248;}
  else {
    arg0K0 = length0_336X;
    goto L23248;}}
 L23248: {
  v_340X = arg0K0;
  Stemp0S = x_334X;
  Stemp1S = y_335X;s48_make_availableAgc((PS_SHIFT_LEFT_INLINE((((1 + (PS_SHIFT_RIGHT_INLINE((23 + (PS_SHIFT_LEFT_INLINE(v_340X, 3))), 3))) + extra0_337X) + extra1_339X), 3)));
  value_341X = Stemp0S;
  Stemp0S = 1;
  if ((0 == (3 & value_341X))) {
    v_342X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_341X, 2)));
    arg3K0 = v_342X;
    goto L26897;}
  else {
    arg3K0 = (((char *) (-3 + value_341X)));
    goto L26897;}}
 L26897: {
  x_343X = arg3K0;
  value_344X = Stemp1S;
  Stemp1S = 1;
  if ((0 == (3 & value_344X))) {
    v_345X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_344X, 2)));
    arg3K0 = v_345X;
    goto L26901;}
  else {
    arg3K0 = (((char *) (-3 + value_344X)));
    goto L26901;}}
 L26901: {
  y_346X = arg3K0;
  external_bignum_347X = (char *) s48_bignum_bitwise_and(x_343X, y_346X);
  v_348X = s48_bignum_fits_in_word_p(external_bignum_347X, 62, 1);
  if (v_348X) {
    n_349X = s48_bignum_to_long(external_bignum_347X);
    return (PS_SHIFT_LEFT_INLINE(n_349X, 2));}
  else {
    return enter_bignum(external_bignum_347X);}}
}
static long integer_bitwise_ior(long x_350X, long y_351X)
{
  char * arg3K0;
  long arg0K1;
  long arg0K0;
  long n_365X;
  char v_364X;
  char * external_bignum_363X;
  char * y_362X;
  char * v_361X;
  long value_360X;
  char * x_359X;
  char * v_358X;
  long value_357X;
  long v_356X;
  long extra1_355X;
  long length1_354X;
  long extra0_353X;
  long length0_352X;
 {  if ((0 == (3 & x_350X))) {
    arg0K0 = 1;
    arg0K1 = 3;
    goto L23175;}
  else {
    arg0K0 = (-1 + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + x_350X))))), 8))), 3)));
    arg0K1 = 0;
    goto L23175;}}
 L23175: {
  length0_352X = arg0K0;
  extra0_353X = arg0K1;
  if ((0 == (3 & y_351X))) {
    arg0K0 = 1;
    arg0K1 = 3;
    goto L23183;}
  else {
    arg0K0 = (-1 + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + y_351X))))), 8))), 3)));
    arg0K1 = 0;
    goto L23183;}}
 L23183: {
  length1_354X = arg0K0;
  extra1_355X = arg0K1;
  if ((length0_352X < length1_354X)) {
    arg0K0 = length1_354X;
    goto L23205;}
  else {
    arg0K0 = length0_352X;
    goto L23205;}}
 L23205: {
  v_356X = arg0K0;
  Stemp0S = x_350X;
  Stemp1S = y_351X;s48_make_availableAgc((PS_SHIFT_LEFT_INLINE((((1 + (PS_SHIFT_RIGHT_INLINE((23 + (PS_SHIFT_LEFT_INLINE(v_356X, 3))), 3))) + extra0_353X) + extra1_355X), 3)));
  value_357X = Stemp0S;
  Stemp0S = 1;
  if ((0 == (3 & value_357X))) {
    v_358X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_357X, 2)));
    arg3K0 = v_358X;
    goto L26971;}
  else {
    arg3K0 = (((char *) (-3 + value_357X)));
    goto L26971;}}
 L26971: {
  x_359X = arg3K0;
  value_360X = Stemp1S;
  Stemp1S = 1;
  if ((0 == (3 & value_360X))) {
    v_361X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_360X, 2)));
    arg3K0 = v_361X;
    goto L26975;}
  else {
    arg3K0 = (((char *) (-3 + value_360X)));
    goto L26975;}}
 L26975: {
  y_362X = arg3K0;
  external_bignum_363X = (char *) s48_bignum_bitwise_ior(x_359X, y_362X);
  v_364X = s48_bignum_fits_in_word_p(external_bignum_363X, 62, 1);
  if (v_364X) {
    n_365X = s48_bignum_to_long(external_bignum_363X);
    return (PS_SHIFT_LEFT_INLINE(n_365X, 2));}
  else {
    return enter_bignum(external_bignum_363X);}}
}
static long integer_bitwise_xor(long x_366X, long y_367X)
{
  char * arg3K0;
  long arg0K1;
  long arg0K0;
  long n_381X;
  char v_380X;
  char * external_bignum_379X;
  char * y_378X;
  char * v_377X;
  long value_376X;
  char * x_375X;
  char * v_374X;
  long value_373X;
  long v_372X;
  long extra1_371X;
  long length1_370X;
  long extra0_369X;
  long length0_368X;
 {  if ((0 == (3 & x_366X))) {
    arg0K0 = 1;
    arg0K1 = 3;
    goto L23132;}
  else {
    arg0K0 = (-1 + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + x_366X))))), 8))), 3)));
    arg0K1 = 0;
    goto L23132;}}
 L23132: {
  length0_368X = arg0K0;
  extra0_369X = arg0K1;
  if ((0 == (3 & y_367X))) {
    arg0K0 = 1;
    arg0K1 = 3;
    goto L23140;}
  else {
    arg0K0 = (-1 + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + y_367X))))), 8))), 3)));
    arg0K1 = 0;
    goto L23140;}}
 L23140: {
  length1_370X = arg0K0;
  extra1_371X = arg0K1;
  if ((length0_368X < length1_370X)) {
    arg0K0 = length1_370X;
    goto L23162;}
  else {
    arg0K0 = length0_368X;
    goto L23162;}}
 L23162: {
  v_372X = arg0K0;
  Stemp0S = x_366X;
  Stemp1S = y_367X;s48_make_availableAgc((PS_SHIFT_LEFT_INLINE((((1 + (PS_SHIFT_RIGHT_INLINE((23 + (PS_SHIFT_LEFT_INLINE(v_372X, 3))), 3))) + extra0_369X) + extra1_371X), 3)));
  value_373X = Stemp0S;
  Stemp0S = 1;
  if ((0 == (3 & value_373X))) {
    v_374X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_373X, 2)));
    arg3K0 = v_374X;
    goto L27045;}
  else {
    arg3K0 = (((char *) (-3 + value_373X)));
    goto L27045;}}
 L27045: {
  x_375X = arg3K0;
  value_376X = Stemp1S;
  Stemp1S = 1;
  if ((0 == (3 & value_376X))) {
    v_377X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_376X, 2)));
    arg3K0 = v_377X;
    goto L27049;}
  else {
    arg3K0 = (((char *) (-3 + value_376X)));
    goto L27049;}}
 L27049: {
  y_378X = arg3K0;
  external_bignum_379X = (char *) s48_bignum_bitwise_xor(x_375X, y_378X);
  v_380X = s48_bignum_fits_in_word_p(external_bignum_379X, 62, 1);
  if (v_380X) {
    n_381X = s48_bignum_to_long(external_bignum_379X);
    return (PS_SHIFT_LEFT_INLINE(n_381X, 2));}
  else {
    return enter_bignum(external_bignum_379X);}}
}
static long Hinteger_op8731(long x_382X, long y_383X)
{
  long arg0K1;
  long arg0K0;
  char * arg3K0;
  long n_395X;
  char v_394X;
  char * external_bignum_393X;
  char * y_392X;
  char * v_391X;
  long value_390X;
  char * x_389X;
  char * v_388X;
  long value_387X;
  long extra1_386X;
  long extra0_385X;
  long length0_384X;
 {  if ((0 == (3 & x_382X))) {
    arg0K0 = 1;
    arg0K1 = 3;
    goto L27135;}
  else {
    arg0K0 = (-1 + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + x_382X))))), 8))), 3)));
    arg0K1 = 0;
    goto L27135;}}
 L27135: {
  length0_384X = arg0K0;
  extra0_385X = arg0K1;
  if ((0 == (3 & y_383X))) {
    arg0K0 = 3;
    goto L27137;}
  else {
    arg0K0 = 0;
    goto L27137;}}
 L27137: {
  extra1_386X = arg0K0;
  Stemp0S = x_382X;
  Stemp1S = y_383X;s48_make_availableAgc((PS_SHIFT_LEFT_INLINE((((6 + (-2 & (PS_SHIFT_RIGHT_INLINE((15 + (PS_SHIFT_LEFT_INLINE(length0_384X, 3))), 2)))) + extra0_385X) + extra1_386X), 3)));
  value_387X = Stemp0S;
  Stemp0S = 1;
  if ((0 == (3 & value_387X))) {
    v_388X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_387X, 2)));
    arg3K0 = v_388X;
    goto L27119;}
  else {
    arg3K0 = (((char *) (-3 + value_387X)));
    goto L27119;}}
 L27119: {
  x_389X = arg3K0;
  value_390X = Stemp1S;
  Stemp1S = 1;
  if ((0 == (3 & value_390X))) {
    v_391X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_390X, 2)));
    arg3K0 = v_391X;
    goto L27123;}
  else {
    arg3K0 = (((char *) (-3 + value_390X)));
    goto L27123;}}
 L27123: {
  y_392X = arg3K0;
  external_bignum_393X = (char *)s48_bignum_quotient(x_389X, y_392X);
  v_394X = s48_bignum_fits_in_word_p(external_bignum_393X, 62, 1);
  if (v_394X) {
    n_395X = s48_bignum_to_long(external_bignum_393X);
    return (PS_SHIFT_LEFT_INLINE(n_395X, 2));}
  else {
    return enter_bignum(external_bignum_393X);}}
}
static long Hinteger_op8662(long x_396X, long y_397X)
{
  long arg0K1;
  long arg0K0;
  char * arg3K0;
  long n_409X;
  char v_408X;
  char * external_bignum_407X;
  char * y_406X;
  char * v_405X;
  long value_404X;
  char * x_403X;
  char * v_402X;
  long value_401X;
  long extra1_400X;
  long extra0_399X;
  long length0_398X;
 {  if ((0 == (3 & x_396X))) {
    arg0K0 = 1;
    arg0K1 = 3;
    goto L27226;}
  else {
    arg0K0 = (-1 + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + x_396X))))), 8))), 3)));
    arg0K1 = 0;
    goto L27226;}}
 L27226: {
  length0_398X = arg0K0;
  extra0_399X = arg0K1;
  if ((0 == (3 & y_397X))) {
    arg0K0 = 3;
    goto L27228;}
  else {
    arg0K0 = 0;
    goto L27228;}}
 L27228: {
  extra1_400X = arg0K0;
  Stemp0S = x_396X;
  Stemp1S = y_397X;s48_make_availableAgc((PS_SHIFT_LEFT_INLINE((((6 + (-2 & (PS_SHIFT_RIGHT_INLINE((15 + (PS_SHIFT_LEFT_INLINE(length0_398X, 3))), 2)))) + extra0_399X) + extra1_400X), 3)));
  value_401X = Stemp0S;
  Stemp0S = 1;
  if ((0 == (3 & value_401X))) {
    v_402X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_401X, 2)));
    arg3K0 = v_402X;
    goto L27210;}
  else {
    arg3K0 = (((char *) (-3 + value_401X)));
    goto L27210;}}
 L27210: {
  x_403X = arg3K0;
  value_404X = Stemp1S;
  Stemp1S = 1;
  if ((0 == (3 & value_404X))) {
    v_405X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_404X, 2)));
    arg3K0 = v_405X;
    goto L27214;}
  else {
    arg3K0 = (((char *) (-3 + value_404X)));
    goto L27214;}}
 L27214: {
  y_406X = arg3K0;
  external_bignum_407X = (char *)s48_bignum_remainder(x_403X, y_406X);
  v_408X = s48_bignum_fits_in_word_p(external_bignum_407X, 62, 1);
  if (v_408X) {
    n_409X = s48_bignum_to_long(external_bignum_407X);
    return (PS_SHIFT_LEFT_INLINE(n_409X, 2));}
  else {
    return enter_bignum(external_bignum_407X);}}
}
static char for_each_imported_binding(char (*proc_410X)(long))
{
  long arg0K0;
  long link_417X;
  char x_416X;
  long entry_415X;
  long link_414X;
  char temp_413X;
  long i_412X;
  long table_411X;
 {  table_411X = Simported_bindingsS;
  arg0K0 = 0;
  goto L24157;}
 L24157: {
  i_412X = arg0K0;
  temp_413X = 1024 == i_412X;
  if (temp_413X) {
    return temp_413X;}
  else {
    link_414X = *((long *) ((((char *) (-3 + table_411X))) + (PS_SHIFT_LEFT_INLINE(i_412X, 3))));
    if ((0 == (3 & link_414X))) {
      arg0K0 = (3 + (-4 & link_414X));
      goto L24129;}
    else {
      arg0K0 = link_414X;
      goto L24129;}}}
 L24129: {
  entry_415X = arg0K0;
  if ((1 == entry_415X)) {
    arg0K0 = (1 + i_412X);
    goto L24157;}
  else {
    x_416X = (*proc_410X)(entry_415X);
    if (x_416X) {
      link_417X = *((long *) ((((char *) (-3 + entry_415X))) + 24));
      if ((0 == (3 & link_417X))) {
        arg0K0 = (3 + (-4 & link_417X));
        goto L24129;}
      else {
        arg0K0 = link_417X;
        goto L24129;}}
    else {
      return 1;}}}
}
static long really_preserve_continuation(long key_418X)
{
  char * arg3K0;
  long arg0K1;
  long arg0K0;
  char * next_431X;
  long pc_430X;
  char * pointer_429X;
  char * pointer_428X;
  long new_427X;
  char * addr_426X;
  long len_425X;
  long size_424X;
  long size_423X;
  char * pointer_422X;
  long previous_421X;
  char * cont_420X;
  long temp_419X;
 {  if (((ScontS) == (Sbottom_of_stackS))) {
    goto L29062;}
  else {
    temp_419X = Sheap_continuationS;
    arg3K0 = (ScontS);
    arg0K1 = 1;
    goto L29032;}}
 L29062: {
  return (Sheap_continuationS);}
 L29032: {
  cont_420X = arg3K0;
  previous_421X = arg0K1;
  if ((cont_420X == (Sbottom_of_stackS))) {
    *((long *) ((((char *) (-3 + previous_421X))) + 16)) = (long) (temp_419X);
    ScontS = (Sbottom_of_stackS);
    goto L29062;}
  else {
    pointer_422X = (((char *) (*((long *) cont_420X)))) + -2;
    size_423X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) pointer_422X)), 8)) + (*((unsigned char *) (pointer_422X + 1)));
    if ((65535 == size_423X)) {
      arg0K0 = (PS_SHIFT_RIGHT_INLINE((*((long *) (cont_420X + 8))), 2));
      goto L25333;}
    else {
      arg0K0 = size_423X;
      goto L25333;}}}
 L25333: {
  size_424X = arg0K0;
  len_425X = 24 + (PS_SHIFT_LEFT_INLINE(size_424X, 3));
  addr_426X = s48_allocate_small((8 + len_425X));
  *((long *) addr_426X) = (long) ((42 + (PS_SHIFT_LEFT_INLINE(len_425X, 8))));
  new_427X = 3 + (((long) (addr_426X + 8)));
  pointer_428X = ((char *) (*((long *) cont_420X)));
  pointer_429X = pointer_428X + -5;
  pc_430X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) pointer_429X)), 8)) + (*((unsigned char *) (pointer_429X + 1)));
  memmove((void *)((((char *) (-3 + new_427X))) + 24), (void *)(cont_420X + 8),(PS_SHIFT_LEFT_INLINE(size_424X, 3)));
  *((long *) (((char *) (-3 + new_427X)))) = (long) ((PS_SHIFT_LEFT_INLINE(pc_430X, 2)));
  *((long *) ((((char *) (-3 + new_427X))) + 8)) = (long) ((3 + (((long) (pointer_428X + (0 - pc_430X))))));
  next_431X = cont_420X + (8 + (PS_SHIFT_LEFT_INLINE(size_424X, 3)));
  if ((3 == (3 & previous_421X))) {
    if ((10 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + previous_421X))))), 2))))) {
      *((long *) ((((char *) (-3 + previous_421X))) + 16)) = (long) (new_427X);
      arg3K0 = next_431X;
      arg0K1 = new_427X;
      goto L29032;}
    else {
      goto L29050;}}
  else {
    goto L29050;}}
 L29050: {
  Sheap_continuationS = new_427X;
  arg3K0 = next_431X;
  arg0K1 = new_427X;
  goto L29032;}
}
static void push_exception_setupB(long exception_432X, long instruction_size_433X)
{
  long n_445X;
  long data_444X;
  long n_443X;
  char * code_pointer_442X;
  long x_441X;
  long bc_pc_440X;
  long code_439X;
  long data_438X;
  long n_437X;
  long pc_436X;
  char * code_pointer_435X;
  long code_434X;
 {  if ((0 == (Snative_exception_contS))) {
    code_434X = current_code_vector();
    code_pointer_435X = (((char *) (-3 + (Sexception_return_codeS)))) + 13;
    pc_436X = PS_SHIFT_LEFT_INLINE(((Scode_pointerS) - (((char *) (-3 + code_434X)))), 2);
    SstackS = ((SstackS) + -40);
    n_437X = PS_SHIFT_RIGHT_INLINE(((ScontS) - (SstackS)), 3);
    data_438X = 3 + (((long) (SstackS)));
    *((long *) (((char *) (-3 + data_438X)))) = (long) ((PS_SHIFT_LEFT_INLINE(n_437X, 2)));
    *((long *) ((((char *) (-3 + data_438X))) + 8)) = (long) (pc_436X);
    *((long *) ((((char *) (-3 + data_438X))) + 16)) = (long) (code_434X);
    *((long *) ((((char *) (-3 + data_438X))) + 24)) = (long) ((PS_SHIFT_LEFT_INLINE(exception_432X, 2)));
    *((long *) ((((char *) (-3 + data_438X))) + 32)) = (long) ((PS_SHIFT_LEFT_INLINE(instruction_size_433X, 2)));
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((((long) code_pointer_435X)));
    ScontS = (SstackS);
    goto L29578;}
  else {
    code_439X = current_code_vector();
    bc_pc_440X = (Scode_pointerS) - (((char *) (-3 + code_439X)));
    x_441X = Snative_exception_contS;
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (x_441X);
    ScontS = (SstackS);
    ps_write_string("handling exception for nc ", (stderr));
    ps_write_integer((Snative_exception_contS), (stderr));
    ps_write_string(" return code pc is ", (stderr));
    ps_write_integer(13, (stderr));
    ps_write_string(" opcode is ", (stderr));
    ps_write_integer((*((unsigned char *) (Scode_pointerS))), (stderr));
    ps_write_string(" exception is ", (stderr));
    ps_write_integer(exception_432X, (stderr));
    ps_write_string(" *val* is ", (stderr));
    ps_write_integer((SvalS), (stderr));
    code_pointer_442X = (((char *) (-3 + (Snative_exception_return_codeS)))) + 13;
    SstackS = ((SstackS) + -32);
    n_443X = PS_SHIFT_RIGHT_INLINE(((ScontS) - (SstackS)), 3);
    data_444X = 3 + (((long) (SstackS)));
    *((long *) (((char *) (-3 + data_444X)))) = (long) ((PS_SHIFT_LEFT_INLINE(n_443X, 2)));
    *((long *) ((((char *) (-3 + data_444X))) + 8)) = (long) ((PS_SHIFT_LEFT_INLINE(exception_432X, 2)));
    *((long *) ((((char *) (-3 + data_444X))) + 16)) = (long) ((PS_SHIFT_LEFT_INLINE(bc_pc_440X, 2)));
    *((long *) ((((char *) (-3 + data_444X))) + 24)) = (long) (code_439X);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((((long) code_pointer_442X)));
    ScontS = (SstackS);
    Snative_exception_contS = 0;
    goto L29578;}}
 L29578: {
  n_445X = *((unsigned char *) (Scode_pointerS));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(n_445X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(exception_432X, 2)));
  return;}
}
static long Hlookup853(long table_446X, long string_447X, long key_448X)
{
  long arg0K0;
  char * addr_461X;
  long value_460X;
  long link_459X;
  long x_458X;
  char * addr_457X;
  long next_456X;
  long len_455X;
  long s2_454X;
  long foo_453X;
  long bucket_452X;
  long link_451X;
  long index_450X;
  long v_449X;
 {  v_449X = Haction5350(string_447X);
  index_450X = 1023 & v_449X;
  link_451X = *((long *) ((((char *) (-3 + table_446X))) + (PS_SHIFT_LEFT_INLINE(index_450X, 3))));
  if ((0 == (3 & link_451X))) {
    arg0K0 = (3 + (-4 & link_451X));
    goto L30474;}
  else {
    arg0K0 = link_451X;
    goto L30474;}}
 L30474: {
  bucket_452X = arg0K0;
  arg0K0 = bucket_452X;
  goto L30480;}
 L30480: {
  foo_453X = arg0K0;
  if ((1 == foo_453X)) {
    if ((3 == (3 & bucket_452X))) {
      arg0K0 = (-4 & bucket_452X);
      goto L30485;}
    else {
      arg0K0 = bucket_452X;
      goto L30485;}}
  else {
    s2_454X = *((long *) (((char *) (-3 + foo_453X))));
    len_455X = PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + string_447X))))), 8);
    if ((len_455X == (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + s2_454X))))), 8)))) {
      if (((!memcmp((void *)(((char *) (-3 + s2_454X))), (void *)(((char *) (-3 + string_447X))),len_455X)))) {
        return foo_453X;}
      else {
        goto L30500;}}
    else {
      goto L30500;}}}
 L30485: {
  next_456X = arg0K0;
  addr_457X = s48_allocate_small(40);
  *((long *) addr_457X) = (long) (8250);
  x_458X = 3 + (((long) (addr_457X + 8)));
  *((long *) (((char *) (-3 + x_458X)))) = (long) (string_447X);
  *((long *) ((((char *) (-3 + x_458X))) + 8)) = (long) (1);
  *((long *) ((((char *) (-3 + x_458X))) + 16)) = (long) (13);
  *((long *) ((((char *) (-3 + x_458X))) + 24)) = (long) (next_456X);
  if ((3 == (3 & x_458X))) {
    arg0K0 = (-4 & x_458X);
    goto L30491;}
  else {
    arg0K0 = x_458X;
    goto L30491;}}
 L30500: {
  link_459X = *((long *) ((((char *) (-3 + foo_453X))) + 24));
  if ((0 == (3 & link_459X))) {
    arg0K0 = (3 + (-4 & link_459X));
    goto L30480;}
  else {
    arg0K0 = link_459X;
    goto L30480;}}
 L30491: {
  value_460X = arg0K0;
  addr_461X = (((char *) (-3 + table_446X))) + (PS_SHIFT_LEFT_INLINE(index_450X, 3));S48_WRITE_BARRIER(table_446X, addr_461X, value_460X);
  *((long *) addr_461X) = (long) (value_460X);
  return x_458X;}
}
static long Hlookup834(long table_462X, long string_463X, long key_464X)
{
  long arg0K0;
  char * addr_477X;
  long value_476X;
  long link_475X;
  long x_474X;
  char * addr_473X;
  long next_472X;
  long len_471X;
  long s2_470X;
  long foo_469X;
  long bucket_468X;
  long link_467X;
  long index_466X;
  long v_465X;
 {  v_465X = Haction5350(string_463X);
  index_466X = 1023 & v_465X;
  link_467X = *((long *) ((((char *) (-3 + table_462X))) + (PS_SHIFT_LEFT_INLINE(index_466X, 3))));
  if ((0 == (3 & link_467X))) {
    arg0K0 = (3 + (-4 & link_467X));
    goto L30617;}
  else {
    arg0K0 = link_467X;
    goto L30617;}}
 L30617: {
  bucket_468X = arg0K0;
  arg0K0 = bucket_468X;
  goto L30623;}
 L30623: {
  foo_469X = arg0K0;
  if ((1 == foo_469X)) {
    if ((3 == (3 & bucket_468X))) {
      arg0K0 = (-4 & bucket_468X);
      goto L30628;}
    else {
      arg0K0 = bucket_468X;
      goto L30628;}}
  else {
    s2_470X = *((long *) (((char *) (-3 + foo_469X))));
    len_471X = PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + string_463X))))), 8);
    if ((len_471X == (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + s2_470X))))), 8)))) {
      if (((!memcmp((void *)(((char *) (-3 + s2_470X))), (void *)(((char *) (-3 + string_463X))),len_471X)))) {
        return foo_469X;}
      else {
        goto L30643;}}
    else {
      goto L30643;}}}
 L30628: {
  next_472X = arg0K0;
  addr_473X = s48_allocate_small(40);
  *((long *) addr_473X) = (long) (8250);
  x_474X = 3 + (((long) (addr_473X + 8)));
  *((long *) (((char *) (-3 + x_474X)))) = (long) (string_463X);
  *((long *) ((((char *) (-3 + x_474X))) + 8)) = (long) (5);
  *((long *) ((((char *) (-3 + x_474X))) + 16)) = (long) (13);
  *((long *) ((((char *) (-3 + x_474X))) + 24)) = (long) (next_472X);
  if ((3 == (3 & x_474X))) {
    arg0K0 = (-4 & x_474X);
    goto L30634;}
  else {
    arg0K0 = x_474X;
    goto L30634;}}
 L30643: {
  link_475X = *((long *) ((((char *) (-3 + foo_469X))) + 24));
  if ((0 == (3 & link_475X))) {
    arg0K0 = (3 + (-4 & link_475X));
    goto L30623;}
  else {
    arg0K0 = link_475X;
    goto L30623;}}
 L30634: {
  value_476X = arg0K0;
  addr_477X = (((char *) (-3 + table_462X))) + (PS_SHIFT_LEFT_INLINE(index_466X, 3));S48_WRITE_BARRIER(table_462X, addr_477X, value_476X);
  *((long *) addr_477X) = (long) (value_476X);
  return x_474X;}
}
static void HtopD12305(char majorP_478X, char in_troubleP_479X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long id_524X;
  long new_523X;
  long x_522X;
  long interrupt_521X;
  long id_520X;
  long status_519X;
  long v_518X;
  char v_517X;
  long channel_516X;
  long i_515X;
  char * addr_514X;
  long val_513X;
  long channel_512X;
  long i_511X;
  char * addr_510X;
  long next_link_509X;
  long new_foo_508X;
  char v_507X;
  char * addr_506X;
  long foo_505X;
  char * addr_504X;
  long l_503X;
  long v_502X;
  long okay_link_501X;
  long foo_link_500X;
  char * addr_499X;
  char * addr_498X;
  char * addr_497X;
  char * addr_496X;
  long val_495X;
  char tracedP_494X;
  long next_493X;
  long thing_492X;
  long pair_491X;
  long alist_490X;
  long l2_489X;
  long goners_488X;
  long okay_487X;
  long alist_486X;
  long foo_link_485X;
  long v_484X;
  long pc_483X;
  long code_482X;
  long i_481X;
  long table_480X;
 {  table_480X = s48_trace_value((Sthe_symbol_tableS));
  arg0K0 = 0;
  goto L32248;}
 L32248: {
  i_481X = arg0K0;
  if ((1024 == i_481X)) {
    Sthe_symbol_tableS = table_480X;
    code_482X = Slast_code_calledS;
    pc_483X = Ssaved_pcS;
    Slast_code_calledS = code_482X;
    Scode_pointerS = ((((char *) (-3 + code_482X))) + pc_483X);
    Slast_code_pointer_resumedS = (Scode_pointerS);
    v_484X = SHARED_REF((Sfinalizer_alistS));
    arg0K0 = v_484X;
    arg0K1 = 25;
    arg0K2 = 25;
    goto L17099;}
  else {
    foo_link_485X = *((long *) ((((char *) (-3 + table_480X))) + (PS_SHIFT_LEFT_INLINE(i_481X, 3))));
    arg0K0 = foo_link_485X;
    arg0K1 = 1;
    goto L21196;}}
 L17099: {
  alist_486X = arg0K0;
  okay_487X = arg0K1;
  goners_488X = arg0K2;
  if ((25 == alist_486X)) {SHARED_SETB((Sfinalizer_alistS), okay_487X);
    l2_489X = Sfinalize_theseS;
    if ((25 == goners_488X)) {
      arg0K0 = l2_489X;
      goto L17106;}
    else {
      arg0K0 = goners_488X;
      goto L17161;}}
  else {
    alist_490X = s48_trace_value(alist_486X);
    pair_491X = s48_trace_value((*((long *) (((char *) (-3 + alist_490X))))));
    thing_492X = *((long *) (((char *) (-3 + pair_491X))));
    next_493X = *((long *) ((((char *) (-3 + alist_490X))) + 8));
    tracedP_494X = s48_extantP(thing_492X);
    val_495X = s48_trace_value(thing_492X);
    addr_496X = ((char *) (-3 + pair_491X));S48_WRITE_BARRIER(pair_491X, addr_496X, val_495X);
    *((long *) addr_496X) = (long) (val_495X);
    addr_497X = ((char *) (-3 + alist_490X));S48_WRITE_BARRIER(alist_490X, addr_497X, pair_491X);
    *((long *) addr_497X) = (long) (pair_491X);
    if (tracedP_494X) {
      addr_498X = (((char *) (-3 + alist_490X))) + 8;S48_WRITE_BARRIER(alist_490X, addr_498X, okay_487X);
      *((long *) addr_498X) = (long) (okay_487X);
      arg0K0 = next_493X;
      arg0K1 = alist_490X;
      arg0K2 = goners_488X;
      goto L17099;}
    else {
      addr_499X = (((char *) (-3 + alist_490X))) + 8;S48_WRITE_BARRIER(alist_490X, addr_499X, goners_488X);
      *((long *) addr_499X) = (long) (goners_488X);
      arg0K0 = next_493X;
      arg0K1 = okay_487X;
      arg0K2 = alist_490X;
      goto L17099;}}}
 L21196: {
  foo_link_500X = arg0K0;
  okay_link_501X = arg0K1;
  if ((0 == (3 & foo_link_500X))) {
    arg0K0 = (3 + (-4 & foo_link_500X));
    goto L21198;}
  else {
    arg0K0 = foo_link_500X;
    goto L21198;}}
 L17106: {
  v_502X = arg0K0;
  Sfinalize_theseS = v_502X;
  arg0K0 = 0;
  goto L17231;}
 L17161: {
  l_503X = arg0K0;
  if ((25 == (*((long *) ((((char *) (-3 + l_503X))) + 8))))) {
    addr_504X = (((char *) (-3 + l_503X))) + 8;S48_WRITE_BARRIER(l_503X, addr_504X, l2_489X);
    *((long *) addr_504X) = (long) (l2_489X);
    arg0K0 = goners_488X;
    goto L17106;}
  else {
    arg0K0 = (*((long *) ((((char *) (-3 + l_503X))) + 8)));
    goto L17161;}}
 L21198: {
  foo_505X = arg0K0;
  if ((1 == foo_505X)) {
    addr_506X = (((char *) (-3 + table_480X))) + (PS_SHIFT_LEFT_INLINE(i_481X, 3));S48_WRITE_BARRIER(table_480X, addr_506X, okay_link_501X);
    *((long *) addr_506X) = (long) (okay_link_501X);
    arg0K0 = (1 + i_481X);
    goto L32248;}
  else {
    v_507X = s48_extantP(foo_505X);
    if (v_507X) {
      new_foo_508X = s48_trace_value(foo_505X);
      next_link_509X = *((long *) ((((char *) (-3 + new_foo_508X))) + 8));
      addr_510X = (((char *) (-3 + new_foo_508X))) + 8;S48_WRITE_BARRIER(new_foo_508X, addr_510X, okay_link_501X);
      *((long *) addr_510X) = (long) (okay_link_501X);
      if ((3 == (3 & new_foo_508X))) {
        arg0K0 = next_link_509X;
        arg0K1 = (-4 & new_foo_508X);
        goto L21196;}
      else {
        arg0K0 = next_link_509X;
        arg0K1 = new_foo_508X;
        goto L21196;}}
    else {
      arg0K0 = (*((long *) ((((char *) (-3 + foo_505X))) + 8)));
      arg0K1 = okay_link_501X;
      goto L21196;}}}
 L17231: {
  i_511X = arg0K0;
  if ((i_511X == (Snumber_of_channelsS))) {
    arg0K0 = 0;
    goto L30096;}
  else {
    channel_512X = *((Svm_channelsS) + i_511X);
    if ((1 == channel_512X)) {
      goto L17259;}
    else {
      if ((0 == (*((long *) (((char *) (-3 + channel_512X))))))) {
        goto L17259;}
      else {
        val_513X = s48_trace_value((*((long *) ((((char *) (-3 + channel_512X))) + 8))));
        addr_514X = (((char *) (-3 + channel_512X))) + 8;S48_WRITE_BARRIER(channel_512X, addr_514X, val_513X);
        *((long *) addr_514X) = (long) (val_513X);
        goto L17259;}}}}
 L30096: {
  i_515X = arg0K0;
  if ((i_515X == (Snumber_of_channelsS))) {
    Sgc_in_troublePS = in_troubleP_479X;
    if (majorP_478X) {
      arg0K0 = 3;
      goto L31457;}
    else {
      arg0K0 = 2;
      goto L31457;}}
  else {
    channel_516X = *((Svm_channelsS) + i_515X);
    if ((1 == channel_516X)) {
      goto L30130;}
    else {
      v_517X = s48_extantP(channel_516X);
      if (v_517X) {
        v_518X = s48_trace_value(channel_516X);
        arg0K0 = v_518X;
        goto L30123;}
      else {
        if ((0 == (*((long *) (((char *) (-3 + channel_516X))))))) {
          arg0K0 = 1;
          goto L30123;}
        else {
          status_519X = close_channelB(channel_516X);
          id_520X = *((long *) ((((char *) (-3 + channel_516X))) + 8));
          if ((status_519X == NO_ERRORS)) {
            goto L30154;}
          else {channel_close_error(status_519X, (*((long *) ((((char *) (-3 + channel_516X))) + 16))), id_520X);
            goto L30154;}}}}}}
 L17259: {
  arg0K0 = (1 + i_511X);
  goto L17231;}
 L31457: {
  interrupt_521X = arg0K0;
  PS_SHIFT_LEFT(1, interrupt_521X, x_522X)
  Spending_interruptsS = ((Spending_interruptsS) | x_522X);
  if ((0 == ((Spending_interruptsS) & (Senabled_interruptsS)))) {
    s48_Sstack_limitS = (Sreal_stack_limitS);
    if ((s48_Spending_eventsPS)) {
      s48_Sstack_limitS = (((char *) -1));
      return;}
    else {
      return;}}
  else {
    s48_Sstack_limitS = (((char *) -1));
    return;}}
 L30130: {
  arg0K0 = (1 + i_515X);
  goto L30096;}
 L30123: {
  new_523X = arg0K0;
  *((Svm_channelsS) + i_515X) = new_523X;
  goto L30130;}
 L30154: {
  if ((1 == (*((long *) ((((char *) (-3 + channel_516X))) + 24))))) {
    id_524X = *((long *) ((((char *) (-3 + channel_516X))) + 8));
    ps_write_string("Channel closed: ", (stderr));
    if ((0 == (3 & id_524X))) {
      ps_write_integer((PS_SHIFT_RIGHT_INLINE(id_524X, 2)), (stderr));
      goto L25826;}
    else {
      if ((3 == (3 & id_524X))) {
        if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + id_524X))))), 2))))) {write_vm_string(id_524X, (stderr));
          goto L25826;}
        else {
          goto L25822;}}
      else {
        goto L25822;}}}
  else {
    arg0K0 = 1;
    goto L30123;}}
 L25826: {
  ps_write_string(" ", (stderr));
  ps_write_integer((PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + channel_516X))) + 16))), 2)), (stderr));
  { long ignoreXX;
  PS_WRITE_CHAR(10, (stderr), ignoreXX) }
  arg0K0 = 1;
  goto L30123;}
 L25822: {
  ps_write_string("<strange id>", (stderr));
  goto L25826;}
}
static void HtopD12316(void)
{
  char * arg3K0;
  long arg0K1;
  long arg0K0;
  long merged_arg0K0;

#ifdef USE_DIRECT_THREADING
  void *Hentry_tracer1025525_return_address;
#else
  int Hentry_tracer1025525_return_tag;
#endif
  long Hentry_tracer10255250_return_value;
  long foo_link_526X;
  char * addr_596X;
  long next_link_595X;
  long new_foo_594X;
  long foo_593X;
  long done_link_592X;
  long foo_link_591X;
  long v_590X;
  long size_589X;
  char * pointer_588X;
  long v_587X;
  long v_586X;
  long v_585X;
  long cells_584X;
  long size_583X;
  char * pointer_582X;
  char * contents_pointer_581X;
  long new_code_580X;
  long mask_size_579X;
  char * code_pointer_578X;
  long pc_577X;
  char * pointer_576X;
  char * pointer_575X;
  char * cont_574X;
  long unused_573X;
  char * a_572X;
  char * addr_571X;
  long value_570X;
  long i_569X;
  char * addr_568X;
  long val_567X;
  char * addr_566X;
  long value_565X;
  long table_564X;
  long i_563X;
  char x_562X;
  long pair_561X;
  long table_560X;
  long v_559X;
  long v_558X;
  long alist_557X;
  long x2_556X;
  char * cell_555X;
  long i_554X;
  long x2_553X;
  char * cell_552X;
  long v_551X;
  long v_550X;
  long v_549X;
  long v_548X;
  long v_547X;
  long v_546X;
  long v_545X;
  long v_544X;
  long v_543X;
  long v_542X;
  long v_541X;
  long v_540X;
  long v_539X;
  long v_538X;
  long v_537X;
  long v_536X;
  long v_535X;
  long v_534X;
  long v_533X;
  long v_532X;
  long code_531X;
  char * frame_530X;
  long length_529X;
  char * frame_528X;
  long v_527X;
 {  v_527X = s48_trace_value((Sempty_logS));
  Sempty_logS = v_527X;
  arg3K0 = (Sexternal_root_stackS);
  goto L11924;}
 L11924: {
  frame_528X = arg3K0;
  if ((frame_528X == NULL)) {
    arg3K0 = (Spermanent_external_rootsS);
    goto L11950;}
  else {
    length_529X = *((long *) frame_528X);
    arg0K0 = 0;
    goto L11932;}}
 L11950: {
  frame_530X = arg3K0;
  if ((frame_530X == NULL)) {s48_trace_external_calls();s48_initializing_gc_root();
    code_531X = current_code_vector();
    Ssaved_pcS = ((Scode_pointerS) - (((char *) (-3 + code_531X))));
    v_532X = s48_trace_value(code_531X);
    Slast_code_calledS = v_532X;
    v_533X = s48_trace_value((SvalS));
    SvalS = v_533X;
    v_534X = s48_trace_value((Scurrent_threadS));
    Scurrent_threadS = v_534X;
    v_535X = s48_trace_value((Sinterrupted_byte_opcode_return_codeS));
    Sinterrupted_byte_opcode_return_codeS = v_535X;
    v_536X = s48_trace_value((Sinterrupted_native_call_return_codeS));
    Sinterrupted_native_call_return_codeS = v_536X;
    v_537X = s48_trace_value((Snative_poll_return_codeS));
    Snative_poll_return_codeS = v_537X;
    v_538X = s48_trace_value((Sexception_return_codeS));
    Sexception_return_codeS = v_538X;
    v_539X = s48_trace_value((Snative_exception_return_codeS));
    Snative_exception_return_codeS = v_539X;
    v_540X = s48_trace_value((Scall_with_values_return_codeS));
    Scall_with_values_return_codeS = v_540X;
    v_541X = s48_trace_value((Sinterrupted_templateS));
    Sinterrupted_templateS = v_541X;
    v_542X = s48_trace_value((s48_Snc_templateS));
    s48_Snc_templateS = v_542X;
    v_543X = SHARED_REF((Ssession_dataS));
    v_544X = s48_trace_value(v_543X);SHARED_SETB((Ssession_dataS), v_544X);
    v_545X = SHARED_REF((Sexception_handlersS));
    v_546X = s48_trace_value(v_545X);SHARED_SETB((Sexception_handlersS), v_546X);
    v_547X = SHARED_REF((Sinterrupt_handlersS));
    v_548X = s48_trace_value(v_547X);SHARED_SETB((Sinterrupt_handlersS), v_548X);
    v_549X = SHARED_REF((Sfinalize_theseS));
    v_550X = s48_trace_value(v_549X);SHARED_SETB((Sfinalize_theseS), v_550X);
    v_551X = SHARED_REF((Sfinalizer_alistS));
    arg0K0 = v_551X;
    goto L13793;}
  else {
    cell_552X = ((char *) (*((long *) (frame_530X + 16))));
    x2_553X = s48_trace_value((*((long *) cell_552X)));
    *((long *) cell_552X) = (long) (x2_553X);
    arg3K0 = (((char *) (*((long *) frame_530X))));
    goto L11950;}}
 L11932: {
  i_554X = arg0K0;
  if ((i_554X == length_529X)) {
    arg3K0 = (((char *) (*((long *) (frame_528X + 8)))));
    goto L11924;}
  else {
    cell_555X = ((char *) (*((long *) (frame_528X + (16 + (PS_SHIFT_LEFT_INLINE(i_554X, 3)))))));
    x2_556X = s48_trace_value((*((long *) cell_555X)));
    *((long *) cell_555X) = (long) (x2_556X);
    arg0K0 = (1 + i_554X);
    goto L11932;}}
 L13793: {
  alist_557X = arg0K0;
  if ((25 == alist_557X)) {
    v_558X = s48_trace_value((Spending_channels_headS));
    Spending_channels_headS = v_558X;
    v_559X = s48_trace_value((Spending_channels_tailS));
    Spending_channels_tailS = v_559X;
    table_560X = s48_trace_value((Simported_bindingsS));
    arg0K0 = 0;
    goto L28769;}
  else {
    pair_561X = *((long *) (((char *) (-3 + alist_557X))));
    x_562X = s48_extantP((*((long *) (((char *) (-3 + pair_561X))))));
    if (x_562X) {
      goto L13818;}
    else {s48_trace_stob_contentsB((*((long *) (((char *) (-3 + pair_561X))))));
      goto L13818;}}}
 L28769: {
  i_563X = arg0K0;
  if ((1024 == i_563X)) {
    Simported_bindingsS = table_560X;
    table_564X = s48_trace_value((Sexported_bindingsS));
    arg0K0 = 0;
    goto L28790;}
  else {
    merged_arg0K0 = (*((long *) ((((char *) (-3 + table_560X))) + (PS_SHIFT_LEFT_INLINE(i_563X, 3)))));
#ifdef USE_DIRECT_THREADING
    Hentry_tracer1025525_return_address = &&Hentry_tracer1025525_return_0;
#else
    Hentry_tracer1025525_return_tag = 0;
#endif
    goto Hentry_tracer1025525;
   Hentry_tracer1025525_return_0:
    value_565X = Hentry_tracer10255250_return_value;
    addr_566X = (((char *) (-3 + table_560X))) + (PS_SHIFT_LEFT_INLINE(i_563X, 3));S48_WRITE_BARRIER(table_560X, addr_566X, value_565X);
    *((long *) addr_566X) = (long) (value_565X);
    arg0K0 = (1 + i_563X);
    goto L28769;}}
 L13818: {
  val_567X = s48_trace_value((*((long *) ((((char *) (-3 + pair_561X))) + 8))));
  addr_568X = (((char *) (-3 + pair_561X))) + 8;S48_WRITE_BARRIER(pair_561X, addr_568X, val_567X);
  *((long *) addr_568X) = (long) (val_567X);
  arg0K0 = (*((long *) ((((char *) (-3 + alist_557X))) + 8)));
  goto L13793;}
 L28790: {
  i_569X = arg0K0;
  if ((1024 == i_569X)) {
    Sexported_bindingsS = table_564X;
    if ((Sstack_warningPS)) {
      arg3K0 = (Sstack_beginS);
      goto L8429;}
    else {
      goto L21429;}}
  else {
    merged_arg0K0 = (*((long *) ((((char *) (-3 + table_564X))) + (PS_SHIFT_LEFT_INLINE(i_569X, 3)))));
#ifdef USE_DIRECT_THREADING
    Hentry_tracer1025525_return_address = &&Hentry_tracer1025525_return_1;
#else
    Hentry_tracer1025525_return_tag = 1;
#endif
    goto Hentry_tracer1025525;
   Hentry_tracer1025525_return_1:
    value_570X = Hentry_tracer10255250_return_value;
    addr_571X = (((char *) (-3 + table_564X))) + (PS_SHIFT_LEFT_INLINE(i_569X, 3));S48_WRITE_BARRIER(table_564X, addr_571X, value_570X);
    *((long *) addr_571X) = (long) (value_570X);
    arg0K0 = (1 + i_569X);
    goto L28790;}}
 L8429: {
  a_572X = arg3K0;
  if ((252645135 == (*((long *) a_572X)))) {
    arg3K0 = (a_572X + 8);
    goto L8429;}
  else {
    unused_573X = PS_SHIFT_RIGHT_INLINE((a_572X - (Sstack_beginS)), 3);
    if ((unused_573X < 30)) {
      { long ignoreXX;
      PS_WRITE_CHAR(10, (stderr), ignoreXX) }
      ps_write_string("[Alert: stack overconsumption (", (stderr));
      ps_write_integer(unused_573X, (stderr));
      ps_write_string("); please inform the Scheme 48 implementors]", (stderr));
      { long ignoreXX;
      PS_WRITE_CHAR(10, (stderr), ignoreXX) }
      Sstack_warningPS = 0;
      goto L21429;}
    else {
      goto L21429;}}}
 L21429: {
s48_trace_locationsB((SstackS), ((SstackS) + (-8 & ((ScontS) - (SstackS)))));
  arg3K0 = (ScontS);
  goto L21439;}
 L21439: {
  cont_574X = arg3K0;
  pointer_575X = ((char *) (*((long *) cont_574X)));
  pointer_576X = pointer_575X + -5;
  pc_577X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) pointer_576X)), 8)) + (*((unsigned char *) (pointer_576X + 1)));
  code_pointer_578X = ((char *) (*((long *) cont_574X)));
  mask_size_579X = *((unsigned char *) (code_pointer_578X + -3));
  new_code_580X = s48_trace_value((3 + (((long) (pointer_575X + (0 - pc_577X))))));
  contents_pointer_581X = cont_574X + 8;
  *((long *) cont_574X) = (long) ((((long) ((((char *) (-3 + new_code_580X))) + pc_577X))));
  if ((0 == mask_size_579X)) {
    pointer_582X = (((char *) (*((long *) cont_574X)))) + -2;
    size_583X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) pointer_582X)), 8)) + (*((unsigned char *) (pointer_582X + 1)));
    if ((65535 == size_583X)) {
      arg0K0 = (PS_SHIFT_RIGHT_INLINE((*((long *) (cont_574X + 8))), 2));
      goto L15810;}
    else {
      arg0K0 = size_583X;
      goto L15810;}}
  else {s48_trace_continuation_contentsB(contents_pointer_581X, code_pointer_578X, mask_size_579X);
    goto L21449;}}
 L15810: {
  cells_584X = arg0K0;s48_trace_locationsB(contents_pointer_581X, (contents_pointer_581X + (PS_SHIFT_LEFT_INLINE(cells_584X, 3))));
  goto L21449;}
 L21449: {
  if ((cont_574X == (Sbottom_of_stackS))) {
    v_585X = s48_trace_value((Sheap_continuationS));
    Sheap_continuationS = v_585X;
    v_586X = s48_trace_value((Stemp0S));
    Stemp0S = v_586X;
    v_587X = s48_trace_value((Stemp1S));
    Stemp1S = v_587X;
    return;}
  else {
    pointer_588X = (((char *) (*((long *) cont_574X)))) + -2;
    size_589X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) pointer_588X)), 8)) + (*((unsigned char *) (pointer_588X + 1)));
    if ((65535 == size_589X)) {
      arg0K0 = (PS_SHIFT_RIGHT_INLINE((*((long *) (cont_574X + 8))), 2));
      goto L21487;}
    else {
      arg0K0 = size_589X;
      goto L21487;}}}
 L21487: {
  v_590X = arg0K0;
  arg3K0 = (cont_574X + (8 + (PS_SHIFT_LEFT_INLINE(v_590X, 3))));
  goto L21439;}
 Hentry_tracer1025525: {
  foo_link_526X = merged_arg0K0;{
  arg0K0 = foo_link_526X;
  arg0K1 = 1;
  goto L21268;}
 L21268: {
  foo_link_591X = arg0K0;
  done_link_592X = arg0K1;
  if ((0 == (3 & foo_link_591X))) {
    arg0K0 = (3 + (-4 & foo_link_591X));
    goto L21270;}
  else {
    arg0K0 = foo_link_591X;
    goto L21270;}}
 L21270: {
  foo_593X = arg0K0;
  if ((1 == foo_593X)) {
    Hentry_tracer10255250_return_value = done_link_592X;
#ifdef USE_DIRECT_THREADING
    goto *Hentry_tracer1025525_return_address;
#else
    goto Hentry_tracer1025525_return;
#endif
}
  else {
    new_foo_594X = s48_trace_value(foo_593X);
    next_link_595X = *((long *) ((((char *) (-3 + new_foo_594X))) + 24));
    addr_596X = (((char *) (-3 + new_foo_594X))) + 24;S48_WRITE_BARRIER(new_foo_594X, addr_596X, done_link_592X);
    *((long *) addr_596X) = (long) (done_link_592X);
    if ((3 == (3 & new_foo_594X))) {
      arg0K0 = next_link_595X;
      arg0K1 = (-4 & new_foo_594X);
      goto L21268;}
    else {
      arg0K0 = next_link_595X;
      arg0K1 = new_foo_594X;
      goto L21268;}}}
#ifndef USE_DIRECT_THREADING
 Hentry_tracer1025525_return:
  switch (Hentry_tracer1025525_return_tag) {
  case 0: goto Hentry_tracer1025525_return_0;
  default: goto Hentry_tracer1025525_return_1;
  }
#endif
}

}
void s48_set_native_protocolB(long protocol_597X)
{

 {  s48_Snative_protocolS = protocol_597X;
  return;}
}
void s48_set_extension_valueB(long value_598X)
{

 {  s48_Sextension_valueS = value_598X;
  return;}
}
long s48_channel_count(void)
{

 {  return (Snumber_of_channelsS);}
}
long *s48_channels(void)
{

 {  return (Svm_channelsS);}
}
long s48_imported_bindings(void)
{

 {  return (Simported_bindingsS);}
}
long s48_exported_bindings(void)
{

 {  return (Sexported_bindingsS);}
}
char s48_os_signal_pending(void)
{
  long arg0K0;
  long v_599X;
 {  if (((Sos_signal_ring_readyS) == (Sos_signal_ring_endS))) {
    return 0;}
  else {
    if ((31 == (Sos_signal_ring_readyS))) {
      arg0K0 = 0;
      goto L3803;}
    else {
      arg0K0 = (1 + (Sos_signal_ring_readyS));
      goto L3803;}}}
 L3803: {
  v_599X = arg0K0;
  Sos_signal_ring_readyS = v_599X;
  return 1;}
}
long s48_symbol_table(void)
{

 {  return (Sthe_symbol_tableS);}
}
char * s48_set_gc_roots_baseB(void)
{
  char * old_base_600X;
 {  old_base_600X = Sexternal_root_stack_baseS;
  Sexternal_root_stack_baseS = (Sexternal_root_stackS);
  return old_base_600X;}
}
char s48_release_gc_roots_baseB(char * old_base_601X)
{
  char * current_base_602X;
 {  current_base_602X = Sexternal_root_stack_baseS;
  Sexternal_root_stack_baseS = old_base_601X;
  if (((Sexternal_root_stackS) == current_base_602X)) {
    return 1;}
  else {
    Sexternal_root_stackS = current_base_602X;
    return 0;}}
}
void s48_reset_external_rootsB(void)
{

 {  Sexternal_root_stackS = NULL;
  Sexternal_root_stack_baseS = NULL;
  Spermanent_external_rootsS = NULL;
  return;}
}
char s48_external_event_readyPUunsafe(void)
{

 {  if ((NULL == (Spending_event_types_readyS))) {
    return 0;}
  else {
    return 1;}}
}
void s48_note_event(void)
{

 {  s48_Spending_eventsPS = 1;
  s48_Sstack_limitS = (((char *) -1));
  return;}
}
void s48_reset_interruptsB(void)
{

 {  Sos_signal_ring_startS = 0;
  Sos_signal_ring_readyS = 0;
  Sos_signal_ring_endS = 0;
  Senabled_interruptsS = 0;
  Spending_interruptsS = 0;
  s48_Spending_interruptPS = 0;
  return;}
}
void s48_disable_interruptsB(void)
{

 {  s48_Spending_interruptPS = 0;
  Senabled_interruptsS = 0;
  return;}
}
void s48_add_os_signal(long sig_603X)
{
  long arg0K0;
  long v_605X;
  long sig_pos_604X;
 {  sig_pos_604X = Sos_signal_ring_endS;
  if ((31 == (Sos_signal_ring_endS))) {
    arg0K0 = 0;
    goto L5003;}
  else {
    arg0K0 = (1 + (Sos_signal_ring_endS));
    goto L5003;}}
 L5003: {
  v_605X = arg0K0;
  Sos_signal_ring_endS = v_605X;
  if (((Sos_signal_ring_startS) == (Sos_signal_ring_endS))) {
    ps_error("OS signal ring too small, report to Scheme 48 maintainers", 0);
    goto L5005;}
  else {
    goto L5005;}}
 L5005: {
  *(Sos_signal_ringS + sig_pos_604X) = sig_603X;
  return;}
}
void s48_push_gc_rootsB(char * frame_606X, long n_607X)
{

 {  *((long *) frame_606X) = (long) (n_607X);
  *((long *) (frame_606X + 8)) = (long) ((((long) (Sexternal_root_stackS))));
  Sexternal_root_stackS = frame_606X;
  return;}
}
char * s48_register_gc_rootB(char * loc_addr_608X)
{
  char * x_610X;
  char * frame_609X;
 {  frame_609X = (char *)malloc(24);
  if ((frame_609X == NULL)) {
    ps_error("out of memory registering a global root", 0);
    goto L5193;}
  else {
    goto L5193;}}
 L5193: {
  *((long *) frame_609X) = (long) ((((long) (Spermanent_external_rootsS))));
  *((long *) (frame_609X + 8)) = (long) ((((long) NULL)));
  x_610X = Spermanent_external_rootsS;
  if ((x_610X == NULL)) {
    goto L5213;}
  else {
    *((long *) ((Spermanent_external_rootsS) + 8)) = (long) ((((long) frame_609X)));
    goto L5213;}}
 L5213: {
  *((long *) (frame_609X + 16)) = (long) ((((long) loc_addr_608X)));
  Spermanent_external_rootsS = frame_609X;
  return frame_609X;}
}
char s48_external_event_pendingPUunsafe(void)
{

 {  if ((NULL == (Spending_event_types_readyS))) {
    return 0;}
  else {
    Spending_event_types_readyS = ((Spending_event_types_readyS)->next);
    return 1;}}
}
long s48_dequeue_external_eventBUunsafe(char *TT0)
{
  long v_613X;
  struct event_type *next_612X;
  struct event_type *type_611X;
 {  type_611X = Spending_event_types_headS;
  next_612X = type_611X->next;
  Spending_event_types_headS = next_612X;
  type_611X->next = (NULL);
  if ((NULL == next_612X)) {
    Spending_event_types_tailS = (NULL);
    goto L5562;}
  else {
    goto L5562;}}
 L5562: {
  v_613X = type_611X->uid;
  if ((NULL == (Spending_event_types_readyS))) {
    *TT0 = 0;
    return v_613X;}
  else {
    *TT0 = 1;
    return v_613X;}}
}
void s48_note_external_eventBUunsafe(long index_614X)
{
  struct event_type *type_615X;
 {  if ((index_614X < (Snumber_of_event_typesS))) {
    goto L6746;}
  else {
    ps_write_string("invalid external event: ", (stderr));
    ps_write_integer(index_614X, (stderr));
    { long ignoreXX;
    PS_WRITE_CHAR(10, (stderr), ignoreXX) }
    ps_error("assertion-violation", 0);
    goto L6746;}}
 L6746: {
  type_615X = *((Sevent_typesS) + index_614X);
  if ((type_615X->usedP)) {
    if ((NULL == (type_615X->next))) {
      if ((type_615X == (Spending_event_types_headS))) {
        return;}
      else {
        if ((type_615X == (Spending_event_types_tailS))) {
          return;}
        else {
          if ((NULL == (Spending_event_types_headS))) {
            Spending_event_types_headS = type_615X;
            Spending_event_types_tailS = type_615X;
            Spending_event_types_readyS = type_615X;
            return;}
          else {
            (Spending_event_types_tailS)->next = type_615X;
            Spending_event_types_tailS = type_615X;
            if ((NULL == (Spending_event_types_readyS))) {
              Spending_event_types_readyS = type_615X;
              return;}
            else {
              return;}}}}}
    else {
      return;}}
  else {
    ps_write_string("invalid external event: ", (stderr));
    ps_write_integer(index_614X, (stderr));
    { long ignoreXX;
    PS_WRITE_CHAR(10, (stderr), ignoreXX) }
    ps_error("assertion-violation", 0);
    return;}}
}
void s48_stack_setB(long x_616X, long value_617X)
{

 {  *((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE(x_616X, 3)))) = (long) (value_617X);
  return;}
}
long s48_stack_ref(long i_618X)
{

 {  return (*((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE(i_618X, 3)))));}
}
void s48_push(long x_619X)
{

 {  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_619X);
  return;}
}
long s48_resetup_external_exception(long new_why_620X, long additional_nargs_621X)
{
  long old_why_623X;
  long old_nargs_622X;
 {  old_nargs_622X = Sexternal_exception_nargsS;
  old_why_623X = *((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE(old_nargs_622X, 3))));
  *((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE(old_nargs_622X, 3)))) = (long) ((PS_SHIFT_LEFT_INLINE(new_why_620X, 2)));
  Sexternal_exception_nargsS = (old_nargs_622X + additional_nargs_621X);
  return old_why_623X;}
}
char s48_pop_gc_rootsB(void)
{

 {  if (((Sexternal_root_stackS) == (Sexternal_root_stack_baseS))) {
    return 0;}
  else {
    Sexternal_root_stackS = (((char *) (*((long *) ((Sexternal_root_stackS) + 8)))));
    return 1;}}
}
void s48_unregister_gc_rootB(char * frame_624X)
{
  char * previous_626X;
  char * next_625X;
 {  if ((frame_624X == (Spermanent_external_rootsS))) {
    Spermanent_external_rootsS = (((char *) (*((long *) frame_624X))));
    goto L9756;}
  else {
    next_625X = ((char *) (*((long *) frame_624X)));
    previous_626X = ((char *) (*((long *) (frame_624X + 8))));
    *((long *) previous_626X) = (long) ((((long) next_625X)));
    if ((next_625X == NULL)) {
      goto L9756;}
    else {
      *((long *) (next_625X + 8)) = (long) ((((long) previous_626X)));
      goto L9756;}}}
 L9756: {
  free(frame_624X);
  return;}
}
char * s48_shorten_bignum(char * external_bignum_627X, long number_of_digits_628X)
{
  long waste_size_633X;
  long old_data_size_632X;
  long new_data_size_631X;
  long new_size_630X;
  long bignum_629X;
 {  bignum_629X = 3 + (((long) external_bignum_627X));
  new_size_630X = 8 + (-8 & (15 + (PS_SHIFT_LEFT_INLINE(number_of_digits_628X, 3))));
  new_data_size_631X = -8 + new_size_630X;
  old_data_size_632X = PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + bignum_629X))))), 8);
  waste_size_633X = old_data_size_632X - new_data_size_631X;
  if ((waste_size_633X < 0)) {
    ps_error("shorten bignum", 2, new_data_size_631X, old_data_size_632X);
    goto L10315;}
  else {
    goto L10315;}}
 L10315: {
  if ((waste_size_633X < 8)) {
    return external_bignum_627X;}
  else {
    *((long *) (((char *) (-11 + bignum_629X)))) = (long) ((78 + (PS_SHIFT_LEFT_INLINE(new_data_size_631X, 8))));
    *((long *) (((char *) (-8 + (((long) ((((char *) (-3 + bignum_629X))) + (-8 & (7 + new_size_630X))))))))) = (long) ((-1970 + (PS_SHIFT_LEFT_INLINE(waste_size_633X, 8))));
    return external_bignum_627X;}}
}
long s48_allocate_bignum(long size_634X)
{
  char * addr_635X;
 {  addr_635X = s48_allocate_small((8 + size_634X));
  *((long *) addr_635X) = (long) ((78 + (PS_SHIFT_LEFT_INLINE(size_634X, 8))));
  return (3 + (((long) (addr_635X + 8))));}
}
void s48_enable_interruptsB(void)
{

 {  Senabled_interruptsS = -1;
  if ((0 == ((Spending_interruptsS) & (Senabled_interruptsS)))) {
    s48_Sstack_limitS = (Sreal_stack_limitS);
    if ((s48_Spending_eventsPS)) {
      s48_Sstack_limitS = (((char *) -1));
      return;}
    else {
      return;}}
  else {
    s48_Sstack_limitS = (((char *) -1));
    return;}}
}
long s48_allocate_string(long len_636X)
{
  long arg0K0;
  long string_639X;
  char * addr_638X;
  long len_637X;
 {  len_637X = PS_SHIFT_LEFT_INLINE(len_636X, 2);
  addr_638X = s48_allocate_untracedAgc((8 + len_637X));
  if ((addr_638X == NULL)) {
    arg0K0 = 1;
    goto L16180;}
  else {
    *((long *) addr_638X) = (long) ((66 + (PS_SHIFT_LEFT_INLINE(len_637X, 8))));
    arg0K0 = (3 + (((long) (addr_638X + 8))));
    goto L16180;}}
 L16180: {
  string_639X = arg0K0;
  if ((1 == string_639X)) {
    ps_error("Out of space, unable to allocate", 0);
    return string_639X;}
  else {
    return string_639X;}}
}
long s48_set_channel_os_index(long channel_640X, long os_index_641X)
{
  char * addr_648X;
  long val_647X;
  long v_646X;
  long x_645X;
  long old_index_644X;
  char x_643X;
  char temp_642X;
 {  temp_642X = os_index_641X < (Snumber_of_channelsS);
  if (temp_642X) {
    goto L17390;}
  else {
    x_643X = add_more_channels(os_index_641X);
    if (x_643X) {
      goto L17390;}
    else {
      return 40;}}}
 L17390: {
  if ((1 == (*((Svm_channelsS) + os_index_641X)))) {
    old_index_644X = PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + channel_640X))) + 16))), 2);
    x_645X = *((long *) ((((char *) (-3 + channel_640X))) + 40));
    if ((5 == x_645X)) {
      v_646X = ps_abort_fd_op(old_index_644X);enqueue_channelB(old_index_644X, v_646X, 1);
      goto L17376;}
    else {
      goto L17376;}}
  else {
    return 48;}}
 L17376: {
  *((Svm_channelsS) + old_index_644X) = 1;
  *((Svm_channelsS) + os_index_641X) = channel_640X;
  val_647X = PS_SHIFT_LEFT_INLINE(os_index_641X, 2);
  addr_648X = (((char *) (-3 + channel_640X))) + 16;S48_WRITE_BARRIER(channel_640X, addr_648X, val_647X);
  *((long *) addr_648X) = (long) (val_647X);
  return 5;}
}
long s48_integer_or_floanum_L(long x_649X, long y_650X)
{
  long v_653X;
  long v_652X;
  long v_651X;
 {  if ((3 == (3 & x_649X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + x_649X))))), 2))))) {
      if (((*((double *) (((char *) (-3 + x_649X))))) < (*((double *) (((char *) (-3 + y_650X))))))) {
        return 5;}
      else {
        return 1;}}
    else {
      goto L20644;}}
  else {
    goto L20644;}}
 L20644: {
  if ((0 == (3 & x_649X))) {
    if ((0 == (3 & y_650X))) {
      if ((x_649X < y_650X)) {
        return 5;}
      else {
        return 1;}}
    else {
      v_651X = s48_bignum_test((((char *) (-3 + y_650X))));
      if ((1 == v_651X)) {
        return 5;}
      else {
        return 1;}}}
  else {
    if ((0 == (3 & y_650X))) {
      v_652X = s48_bignum_test((((char *) (-3 + x_649X))));
      if ((1 == v_652X)) {
        return 1;}
      else {
        return 5;}}
    else {
      v_653X = s48_bignum_compare((((char *) (-3 + x_649X))), (((char *) (-3 + y_650X))));
      if ((-1 == v_653X)) {
        return 5;}
      else {
        return 1;}}}}
}
long s48_integer_or_floanum_G(long x_654X, long y_655X)
{
  long v_658X;
  long v_657X;
  long v_656X;
 {  if ((3 == (3 & x_654X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + x_654X))))), 2))))) {
      if (((*((double *) (((char *) (-3 + y_655X))))) < (*((double *) (((char *) (-3 + x_654X))))))) {
        return 5;}
      else {
        return 1;}}
    else {
      goto L20773;}}
  else {
    goto L20773;}}
 L20773: {
  if ((0 == (3 & y_655X))) {
    if ((0 == (3 & x_654X))) {
      if ((y_655X < x_654X)) {
        return 5;}
      else {
        return 1;}}
    else {
      v_656X = s48_bignum_test((((char *) (-3 + x_654X))));
      if ((1 == v_656X)) {
        return 5;}
      else {
        return 1;}}}
  else {
    if ((0 == (3 & x_654X))) {
      v_657X = s48_bignum_test((((char *) (-3 + y_655X))));
      if ((1 == v_657X)) {
        return 1;}
      else {
        return 5;}}
    else {
      v_658X = s48_bignum_compare((((char *) (-3 + y_655X))), (((char *) (-3 + x_654X))));
      if ((-1 == v_658X)) {
        return 5;}
      else {
        return 1;}}}}
}
long s48_integer_or_floanum_LE(long x_659X, long y_660X)
{
  char b_661X;
 {  if ((3 == (3 & x_659X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + x_659X))))), 2))))) {
      if (((*((double *) (((char *) (-3 + y_660X))))) < (*((double *) (((char *) (-3 + x_659X))))))) {
        return 1;}
      else {
        return 5;}}
    else {
      goto L20902;}}
  else {
    goto L20902;}}
 L20902: {
  b_661X = integerLE(x_659X, y_660X);
  if (b_661X) {
    return 5;}
  else {
    return 1;}}
}
long s48_integer_or_floanum_GE(long x_662X, long y_663X)
{
  char b_664X;
 {  if ((3 == (3 & x_662X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + x_662X))))), 2))))) {
      if (((*((double *) (((char *) (-3 + x_662X))))) < (*((double *) (((char *) (-3 + y_663X))))))) {
        return 1;}
      else {
        return 5;}}
    else {
      goto L20979;}}
  else {
    goto L20979;}}
 L20979: {
  b_664X = integerGE(x_662X, y_663X);
  if (b_664X) {
    return 5;}
  else {
    return 1;}}
}
long s48_make_blank_return_code(long protocol_665X, long template_666X, long frame_size_667X, long opcode_count_668X)
{

 {s48_make_availableAgc((8 + (-8 & (22 + opcode_count_668X))));
  return make_blank_return_code(protocol_665X, template_666X, frame_size_667X, opcode_count_668X, 0);}
}
long s48_enter_string_utf_8(char * p_669X)
{
  long arg0K1;
  long arg0K0;
  long vm_681X;
  long string_680X;
  char * addr_679X;
  long len_678X;
  long decoded_677X;
  long consumed_676X;
  long count_675X;
  long value_674X;
  char incompleteP_673X;
  long target_index_672X;
  long index_671X;
  long size_670X;
 {  size_670X = strlen((char *) (((char *)p_669X)));
  arg0K0 = 0;
  arg0K1 = 0;
  goto L22414;}
 L22414: {
  index_671X = arg0K0;
  target_index_672X = arg0K1;
  if ((index_671X < size_670X)) {decode_scalar_valueUutf_8((p_669X + index_671X), (size_670X - index_671X), &incompleteP_673X, &value_674X, &count_675X);
    if (incompleteP_673X) {
      arg0K0 = index_671X;
      arg0K1 = target_index_672X;
      goto L22391;}
    else {
      arg0K0 = (index_671X + count_675X);
      arg0K1 = (1 + target_index_672X);
      goto L22414;}}
  else {
    arg0K0 = index_671X;
    arg0K1 = target_index_672X;
    goto L22391;}}
 L22391: {
  consumed_676X = arg0K0;
  decoded_677X = arg0K1;
  len_678X = PS_SHIFT_LEFT_INLINE(decoded_677X, 2);
  addr_679X = s48_allocate_untracedAgc((8 + len_678X));
  if ((addr_679X == NULL)) {
    arg0K0 = 1;
    goto L22429;}
  else {
    *((long *) addr_679X) = (long) ((66 + (PS_SHIFT_LEFT_INLINE(len_678X, 8))));
    arg0K0 = (3 + (((long) (addr_679X + 8))));
    goto L22429;}}
 L22429: {
  string_680X = arg0K0;
  if ((1 == string_680X)) {
    ps_error("Out of space, unable to allocate", 0);
    arg0K0 = string_680X;
    goto L22397;}
  else {
    arg0K0 = string_680X;
    goto L22397;}}
 L22397: {
  vm_681X = arg0K0;decodeUutf_8B(p_669X, vm_681X, consumed_676X);
  return vm_681X;}
}
long s48_enter_string_utf_8_n(char * p_682X, long size_683X)
{
  long arg0K1;
  long arg0K0;
  long vm_694X;
  long string_693X;
  char * addr_692X;
  long len_691X;
  long decoded_690X;
  long consumed_689X;
  long count_688X;
  long value_687X;
  char incompleteP_686X;
  long target_index_685X;
  long index_684X;
 {  arg0K0 = 0;
  arg0K1 = 0;
  goto L22471;}
 L22471: {
  index_684X = arg0K0;
  target_index_685X = arg0K1;
  if ((index_684X < size_683X)) {decode_scalar_valueUutf_8((p_682X + index_684X), (size_683X - index_684X), &incompleteP_686X, &value_687X, &count_688X);
    if (incompleteP_686X) {
      arg0K0 = index_684X;
      arg0K1 = target_index_685X;
      goto L22451;}
    else {
      arg0K0 = (index_684X + count_688X);
      arg0K1 = (1 + target_index_685X);
      goto L22471;}}
  else {
    arg0K0 = index_684X;
    arg0K1 = target_index_685X;
    goto L22451;}}
 L22451: {
  consumed_689X = arg0K0;
  decoded_690X = arg0K1;
  len_691X = PS_SHIFT_LEFT_INLINE(decoded_690X, 2);
  addr_692X = s48_allocate_untracedAgc((8 + len_691X));
  if ((addr_692X == NULL)) {
    arg0K0 = 1;
    goto L22486;}
  else {
    *((long *) addr_692X) = (long) ((66 + (PS_SHIFT_LEFT_INLINE(len_691X, 8))));
    arg0K0 = (3 + (((long) (addr_692X + 8))));
    goto L22486;}}
 L22486: {
  string_693X = arg0K0;
  if ((1 == string_693X)) {
    ps_error("Out of space, unable to allocate", 0);
    arg0K0 = string_693X;
    goto L22457;}
  else {
    arg0K0 = string_693X;
    goto L22457;}}
 L22457: {
  vm_694X = arg0K0;decodeUutf_8B(p_682X, vm_694X, consumed_689X);
  return vm_694X;}
}
long s48_enter_string_utf_16beU(char * p_695X)
{
  long arg0K1;
  long arg0K0;
  long vm_708X;
  long string_707X;
  char * addr_706X;
  long len_705X;
  long decoded_704X;
  long consumed_703X;
  long count_702X;
  long value_701X;
  char incompleteP_700X;
  long target_index_699X;
  long index_698X;
  long i_697X;
  char *s_696X;
 {  s_696X = ((char *)p_695X);
  arg0K0 = 0;
  goto L22529;}
 L22529: {
  i_697X = arg0K0;
  if ((0 == (((unsigned char) (*(s_696X + i_697X)))))) {
    if ((0 == (((unsigned char) (*(s_696X + (1 + i_697X))))))) {
      arg0K0 = 0;
      arg0K1 = 0;
      goto L22547;}
    else {
      goto L22530;}}
  else {
    goto L22530;}}
 L22547: {
  index_698X = arg0K0;
  target_index_699X = arg0K1;
  if ((index_698X < i_697X)) {decode_scalar_valueUutf_16be((p_695X + index_698X), (i_697X - index_698X), &incompleteP_700X, &value_701X, &count_702X);
    if (incompleteP_700X) {
      arg0K0 = index_698X;
      arg0K1 = target_index_699X;
      goto L22509;}
    else {
      arg0K0 = (index_698X + count_702X);
      arg0K1 = (1 + target_index_699X);
      goto L22547;}}
  else {
    arg0K0 = index_698X;
    arg0K1 = target_index_699X;
    goto L22509;}}
 L22530: {
  arg0K0 = (2 + i_697X);
  goto L22529;}
 L22509: {
  consumed_703X = arg0K0;
  decoded_704X = arg0K1;
  len_705X = PS_SHIFT_LEFT_INLINE(decoded_704X, 2);
  addr_706X = s48_allocate_untracedAgc((8 + len_705X));
  if ((addr_706X == NULL)) {
    arg0K0 = 1;
    goto L22562;}
  else {
    *((long *) addr_706X) = (long) ((66 + (PS_SHIFT_LEFT_INLINE(len_705X, 8))));
    arg0K0 = (3 + (((long) (addr_706X + 8))));
    goto L22562;}}
 L22562: {
  string_707X = arg0K0;
  if ((1 == string_707X)) {
    ps_error("Out of space, unable to allocate", 0);
    arg0K0 = string_707X;
    goto L22515;}
  else {
    arg0K0 = string_707X;
    goto L22515;}}
 L22515: {
  vm_708X = arg0K0;decodeUutf_16beB(p_695X, vm_708X, consumed_703X);
  return vm_708X;}
}
long s48_enter_string_utf_16be_nU(char * p_709X, long size_710X)
{
  long arg0K1;
  long arg0K0;
  long vm_721X;
  long string_720X;
  char * addr_719X;
  long len_718X;
  long decoded_717X;
  long consumed_716X;
  long count_715X;
  long value_714X;
  char incompleteP_713X;
  long target_index_712X;
  long index_711X;
 {  arg0K0 = 0;
  arg0K1 = 0;
  goto L22604;}
 L22604: {
  index_711X = arg0K0;
  target_index_712X = arg0K1;
  if ((index_711X < size_710X)) {decode_scalar_valueUutf_16be((p_709X + index_711X), (size_710X - index_711X), &incompleteP_713X, &value_714X, &count_715X);
    if (incompleteP_713X) {
      arg0K0 = index_711X;
      arg0K1 = target_index_712X;
      goto L22584;}
    else {
      arg0K0 = (index_711X + count_715X);
      arg0K1 = (1 + target_index_712X);
      goto L22604;}}
  else {
    arg0K0 = index_711X;
    arg0K1 = target_index_712X;
    goto L22584;}}
 L22584: {
  consumed_716X = arg0K0;
  decoded_717X = arg0K1;
  len_718X = PS_SHIFT_LEFT_INLINE(decoded_717X, 2);
  addr_719X = s48_allocate_untracedAgc((8 + len_718X));
  if ((addr_719X == NULL)) {
    arg0K0 = 1;
    goto L22619;}
  else {
    *((long *) addr_719X) = (long) ((66 + (PS_SHIFT_LEFT_INLINE(len_718X, 8))));
    arg0K0 = (3 + (((long) (addr_719X + 8))));
    goto L22619;}}
 L22619: {
  string_720X = arg0K0;
  if ((1 == string_720X)) {
    ps_error("Out of space, unable to allocate", 0);
    arg0K0 = string_720X;
    goto L22590;}
  else {
    arg0K0 = string_720X;
    goto L22590;}}
 L22590: {
  vm_721X = arg0K0;decodeUutf_16beB(p_709X, vm_721X, consumed_716X);
  return vm_721X;}
}
long s48_enter_string_utf_16leU(char * p_722X)
{
  long arg0K1;
  long arg0K0;
  long vm_735X;
  long string_734X;
  char * addr_733X;
  long len_732X;
  long decoded_731X;
  long consumed_730X;
  long count_729X;
  long value_728X;
  char incompleteP_727X;
  long target_index_726X;
  long index_725X;
  long i_724X;
  char *s_723X;
 {  s_723X = ((char *)p_722X);
  arg0K0 = 0;
  goto L22662;}
 L22662: {
  i_724X = arg0K0;
  if ((0 == (((unsigned char) (*(s_723X + i_724X)))))) {
    if ((0 == (((unsigned char) (*(s_723X + (1 + i_724X))))))) {
      arg0K0 = 0;
      arg0K1 = 0;
      goto L22680;}
    else {
      goto L22663;}}
  else {
    goto L22663;}}
 L22680: {
  index_725X = arg0K0;
  target_index_726X = arg0K1;
  if ((index_725X < i_724X)) {decode_scalar_valueUutf_16le((p_722X + index_725X), (i_724X - index_725X), &incompleteP_727X, &value_728X, &count_729X);
    if (incompleteP_727X) {
      arg0K0 = index_725X;
      arg0K1 = target_index_726X;
      goto L22642;}
    else {
      arg0K0 = (index_725X + count_729X);
      arg0K1 = (1 + target_index_726X);
      goto L22680;}}
  else {
    arg0K0 = index_725X;
    arg0K1 = target_index_726X;
    goto L22642;}}
 L22663: {
  arg0K0 = (2 + i_724X);
  goto L22662;}
 L22642: {
  consumed_730X = arg0K0;
  decoded_731X = arg0K1;
  len_732X = PS_SHIFT_LEFT_INLINE(decoded_731X, 2);
  addr_733X = s48_allocate_untracedAgc((8 + len_732X));
  if ((addr_733X == NULL)) {
    arg0K0 = 1;
    goto L22695;}
  else {
    *((long *) addr_733X) = (long) ((66 + (PS_SHIFT_LEFT_INLINE(len_732X, 8))));
    arg0K0 = (3 + (((long) (addr_733X + 8))));
    goto L22695;}}
 L22695: {
  string_734X = arg0K0;
  if ((1 == string_734X)) {
    ps_error("Out of space, unable to allocate", 0);
    arg0K0 = string_734X;
    goto L22648;}
  else {
    arg0K0 = string_734X;
    goto L22648;}}
 L22648: {
  vm_735X = arg0K0;decodeUutf_16leB(p_722X, vm_735X, consumed_730X);
  return vm_735X;}
}
long s48_enter_string_utf_16le_nU(char * p_736X, long size_737X)
{
  long arg0K1;
  long arg0K0;
  long vm_748X;
  long string_747X;
  char * addr_746X;
  long len_745X;
  long decoded_744X;
  long consumed_743X;
  long count_742X;
  long value_741X;
  char incompleteP_740X;
  long target_index_739X;
  long index_738X;
 {  arg0K0 = 0;
  arg0K1 = 0;
  goto L22737;}
 L22737: {
  index_738X = arg0K0;
  target_index_739X = arg0K1;
  if ((index_738X < size_737X)) {decode_scalar_valueUutf_16le((p_736X + index_738X), (size_737X - index_738X), &incompleteP_740X, &value_741X, &count_742X);
    if (incompleteP_740X) {
      arg0K0 = index_738X;
      arg0K1 = target_index_739X;
      goto L22717;}
    else {
      arg0K0 = (index_738X + count_742X);
      arg0K1 = (1 + target_index_739X);
      goto L22737;}}
  else {
    arg0K0 = index_738X;
    arg0K1 = target_index_739X;
    goto L22717;}}
 L22717: {
  consumed_743X = arg0K0;
  decoded_744X = arg0K1;
  len_745X = PS_SHIFT_LEFT_INLINE(decoded_744X, 2);
  addr_746X = s48_allocate_untracedAgc((8 + len_745X));
  if ((addr_746X == NULL)) {
    arg0K0 = 1;
    goto L22752;}
  else {
    *((long *) addr_746X) = (long) ((66 + (PS_SHIFT_LEFT_INLINE(len_745X, 8))));
    arg0K0 = (3 + (((long) (addr_746X + 8))));
    goto L22752;}}
 L22752: {
  string_747X = arg0K0;
  if ((1 == string_747X)) {
    ps_error("Out of space, unable to allocate", 0);
    arg0K0 = string_747X;
    goto L22723;}
  else {
    arg0K0 = string_747X;
    goto L22723;}}
 L22723: {
  vm_748X = arg0K0;decodeUutf_16leB(p_736X, vm_748X, consumed_743X);
  return vm_748X;}
}
long s48_integer_or_floanum_E(long x_749X, long y_750X)
{
  char arg4K0;
  char v_752X;
  char b_751X;
 {  if ((3 == (3 & x_749X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + x_749X))))), 2))))) {
      arg4K0 = ((*((double *) (((char *) (-3 + x_749X))))) == (*((double *) (((char *) (-3 + y_750X))))));
      goto L23781;}
    else {
      goto L23777;}}
  else {
    goto L23777;}}
 L23781: {
  b_751X = arg4K0;
  if (b_751X) {
    return 5;}
  else {
    return 1;}}
 L23777: {
  v_752X = integerE(x_749X, y_750X);
  arg4K0 = v_752X;
  goto L23781;}
}
void s48_close_channel(long os_index_753X)
{
  long obj_754X;
 {  if ((os_index_753X < 0)) {
    return;}
  else {
    if ((os_index_753X < (Snumber_of_channelsS))) {
      obj_754X = *((Svm_channelsS) + os_index_753X);
      if ((3 == (3 & obj_754X))) {
        if ((6 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_754X))))), 2))))) {close_channelB((*((Svm_channelsS) + os_index_753X)));
          return;}
        else {
          return;}}
      else {
        return;}}
    else {
      return;}}}
}
long s48_enter_string_latin_1_n(char *s_755X, long count_756X)
{

 {  return enter_stringAgc_n(s_755X, count_756X);}
}
void s48_string_set(long s_757X, long i_758X, long c_759X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long shifted_764X;
  long j_763X;
  long bits_762X;
  long max_761X;
  long v_760X;
 {  if ((3 == (3 & s_757X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + s_757X))))), 2))))) {
      goto L27358;}
    else {s48_argument_type_violation(s_757X);
      goto L27358;}}
  else {s48_argument_type_violation(s_757X);
    goto L27358;}}
 L27358: {
  v_760X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + s_757X))))), 8)) / 4;
  max_761X = -1 + v_760X;
  if ((i_758X < 0)) {
    goto L27380;}
  else {
    if ((max_761X < i_758X)) {
      goto L27380;}
    else {
      goto L27360;}}}
 L27380: {
s48_range_violation((PS_SHIFT_LEFT_INLINE(i_758X, 2)), 0, (PS_SHIFT_LEFT_INLINE(max_761X, 2)));
  goto L27360;}
 L27360: {
  arg0K0 = 0;
  arg0K1 = 0;
  arg0K2 = c_759X;
  goto L27400;}
 L27400: {
  bits_762X = arg0K0;
  j_763X = arg0K1;
  shifted_764X = arg0K2;
  if ((j_763X < 4)) {
    *((unsigned char *) ((((char *) (-3 + s_757X))) + ((PS_SHIFT_LEFT_INLINE(i_758X, 2)) + j_763X))) = (unsigned char) ((255 & shifted_764X));
    arg0K0 = (8 + bits_762X);
    arg0K1 = (1 + j_763X);
    arg0K2 = (PS_SHIFT_RIGHT_LOGICAL_INLINE(shifted_764X, 8));
    goto L27400;}
  else {
    return;}}
}
long s48_string_ref(long s_765X, long i_766X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long x_772X;
  long scalar_value_771X;
  long j_770X;
  long bits_769X;
  long max_768X;
  long v_767X;
 {  if ((3 == (3 & s_765X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + s_765X))))), 2))))) {
      goto L27422;}
    else {s48_argument_type_violation(s_765X);
      goto L27422;}}
  else {s48_argument_type_violation(s_765X);
    goto L27422;}}
 L27422: {
  v_767X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + s_765X))))), 8)) / 4;
  max_768X = -1 + v_767X;
  if ((i_766X < 0)) {
    goto L27444;}
  else {
    if ((max_768X < i_766X)) {
      goto L27444;}
    else {
      goto L27424;}}}
 L27444: {
s48_range_violation((PS_SHIFT_LEFT_INLINE(i_766X, 2)), 0, (PS_SHIFT_LEFT_INLINE(max_768X, 2)));
  goto L27424;}
 L27424: {
  arg0K0 = 0;
  arg0K1 = 0;
  arg0K2 = 0;
  goto L27463;}
 L27463: {
  bits_769X = arg0K0;
  j_770X = arg0K1;
  scalar_value_771X = arg0K2;
  if ((j_770X < 4)) {
    PS_SHIFT_LEFT((*((unsigned char *) ((((char *) (-3 + s_765X))) + ((PS_SHIFT_LEFT_INLINE(i_766X, 2)) + j_770X)))), bits_769X, x_772X)
    arg0K0 = (8 + bits_769X);
    arg0K1 = (1 + j_770X);
    arg0K2 = (x_772X + scalar_value_771X);
    goto L27463;}
  else {
    return scalar_value_771X;}}
}
long s48_string_length(long s_773X)
{

 {  if ((3 == (3 & s_773X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + s_773X))))), 2))))) {
      goto L27482;}
    else {s48_argument_type_violation(s_773X);
      goto L27482;}}
  else {s48_argument_type_violation(s_773X);
    goto L27482;}}
 L27482: {
  return ((PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + s_773X))))), 8)) / 4);}
}
void s48_copy_latin_1_to_string_n(char *string_774X, long len_775X, long vm_string_776X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long shifted_782X;
  long j_781X;
  long bits_780X;
  long c_779X;
  long i_778X;
  long max_777X;
 {  if ((3 == (3 & vm_string_776X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + vm_string_776X))))), 2))))) {
      goto L27510;}
    else {s48_argument_type_violation(vm_string_776X);
      goto L27510;}}
  else {s48_argument_type_violation(vm_string_776X);
    goto L27510;}}
 L27510: {
  max_777X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_776X))))), 8)) / 4;
  if ((len_775X < 0)) {
    goto L27534;}
  else {
    if ((max_777X < len_775X)) {
      goto L27534;}
    else {
      goto L27514;}}}
 L27534: {
s48_range_violation((PS_SHIFT_LEFT_INLINE(len_775X, 2)), 0, (PS_SHIFT_LEFT_INLINE(max_777X, 2)));
  goto L27514;}
 L27514: {
  arg0K0 = 0;
  goto L27552;}
 L27552: {
  i_778X = arg0K0;
  if ((i_778X < len_775X)) {
    c_779X = ((unsigned char) (*(string_774X + i_778X)));
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = c_779X;
    goto L27563;}
  else {
    return;}}
 L27563: {
  bits_780X = arg0K0;
  j_781X = arg0K1;
  shifted_782X = arg0K2;
  if ((j_781X < 4)) {
    *((unsigned char *) ((((char *) (-3 + vm_string_776X))) + ((PS_SHIFT_LEFT_INLINE(i_778X, 2)) + j_781X))) = (unsigned char) ((255 & shifted_782X));
    arg0K0 = (8 + bits_780X);
    arg0K1 = (1 + j_781X);
    arg0K2 = (PS_SHIFT_RIGHT_LOGICAL_INLINE(shifted_782X, 8));
    goto L27563;}
  else {
    arg0K0 = (1 + i_778X);
    goto L27552;}}
}
void s48_copy_latin_1_to_string(char *string_783X, long vm_string_784X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long shifted_791X;
  long j_790X;
  long bits_789X;
  long c_788X;
  long i_787X;
  long i_786X;
  long max_785X;
 {  if ((3 == (3 & vm_string_784X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + vm_string_784X))))), 2))))) {
      goto L27586;}
    else {s48_argument_type_violation(vm_string_784X);
      goto L27586;}}
  else {s48_argument_type_violation(vm_string_784X);
    goto L27586;}}
 L27586: {
  max_785X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_784X))))), 8)) / 4;
  i_786X = strlen((char *) string_783X);
  if ((i_786X < 0)) {
    goto L27612;}
  else {
    if ((max_785X < i_786X)) {
      goto L27612;}
    else {
      goto L27592;}}}
 L27612: {
s48_range_violation((PS_SHIFT_LEFT_INLINE(i_786X, 2)), 0, (PS_SHIFT_LEFT_INLINE(max_785X, 2)));
  goto L27592;}
 L27592: {
  arg0K0 = 0;
  goto L27630;}
 L27630: {
  i_787X = arg0K0;
  if ((i_787X < (strlen((char *) string_783X)))) {
    c_788X = ((unsigned char) (*(string_783X + i_787X)));
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = c_788X;
    goto L27641;}
  else {
    return;}}
 L27641: {
  bits_789X = arg0K0;
  j_790X = arg0K1;
  shifted_791X = arg0K2;
  if ((j_790X < 4)) {
    *((unsigned char *) ((((char *) (-3 + vm_string_784X))) + ((PS_SHIFT_LEFT_INLINE(i_787X, 2)) + j_790X))) = (unsigned char) ((255 & shifted_791X));
    arg0K0 = (8 + bits_789X);
    arg0K1 = (1 + j_790X);
    arg0K2 = (PS_SHIFT_RIGHT_LOGICAL_INLINE(shifted_791X, 8));
    goto L27641;}
  else {
    arg0K0 = (1 + i_787X);
    goto L27630;}}
}
void s48_copy_string_to_latin_1(long vm_string_792X, char *string_793X)
{
  long v_794X;
 {  if ((3 == (3 & vm_string_792X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + vm_string_792X))))), 2))))) {
      goto L27664;}
    else {s48_argument_type_violation(vm_string_792X);
      goto L27664;}}
  else {s48_argument_type_violation(vm_string_792X);
    goto L27664;}}
 L27664: {
  v_794X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_792X))))), 8)) / 4;
  copy_vm_string_to_stringUlatin_1B(vm_string_792X, 0, v_794X, string_793X);
  return;}
}
void s48_copy_string_to_latin_1_n(long vm_string_795X, long start_796X, long count_797X, char *string_798X)
{
  long max_802X;
  long v_801X;
  long max_800X;
  long v_799X;
 {  if ((3 == (3 & vm_string_795X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + vm_string_795X))))), 2))))) {
      goto L27695;}
    else {s48_argument_type_violation(vm_string_795X);
      goto L27695;}}
  else {s48_argument_type_violation(vm_string_795X);
    goto L27695;}}
 L27695: {
  v_799X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_795X))))), 8)) / 4;
  max_800X = -1 + v_799X;
  if ((start_796X < 0)) {
    goto L27721;}
  else {
    if ((max_800X < start_796X)) {
      goto L27721;}
    else {
      goto L27697;}}}
 L27721: {
s48_range_violation((PS_SHIFT_LEFT_INLINE(start_796X, 2)), 0, (PS_SHIFT_LEFT_INLINE(max_800X, 2)));
  goto L27697;}
 L27697: {
  v_801X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_795X))))), 8)) / 4;
  max_802X = v_801X - start_796X;
  if ((count_797X < 0)) {
    goto L27738;}
  else {
    if ((max_802X < count_797X)) {
      goto L27738;}
    else {
      copy_vm_string_to_stringUlatin_1B(vm_string_795X, start_796X, count_797X, string_798X);
      return;}}}
 L27738: {
s48_range_violation((PS_SHIFT_LEFT_INLINE(count_797X, 2)), 0, (PS_SHIFT_LEFT_INLINE(max_802X, 2)));
  copy_vm_string_to_stringUlatin_1B(vm_string_795X, start_796X, count_797X, string_798X);
  return;}
}
long s48_string_utf_8_length(long vm_string_803X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long count_812X;
  char out_of_spaceP_811X;
  long x_810X;
  long scalar_value_809X;
  long j_808X;
  long bits_807X;
  long char_index_806X;
  long encoding_length_805X;
  long count_804X;
 {  if ((3 == (3 & vm_string_803X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + vm_string_803X))))), 2))))) {
      goto L27767;}
    else {s48_argument_type_violation(vm_string_803X);
      goto L27767;}}
  else {s48_argument_type_violation(vm_string_803X);
    goto L27767;}}
 L27767: {
  count_804X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_803X))))), 8)) / 4;
  arg0K0 = 0;
  arg0K1 = 0;
  goto L27794;}
 L27794: {
  encoding_length_805X = arg0K0;
  char_index_806X = arg0K1;
  if ((char_index_806X < count_804X)) {
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = 0;
    goto L27803;}
  else {
    return encoding_length_805X;}}
 L27803: {
  bits_807X = arg0K0;
  j_808X = arg0K1;
  scalar_value_809X = arg0K2;
  if ((j_808X < 4)) {
    PS_SHIFT_LEFT((*((unsigned char *) ((((char *) (-3 + vm_string_803X))) + ((PS_SHIFT_LEFT_INLINE(char_index_806X, 2)) + j_808X)))), bits_807X, x_810X)
    arg0K0 = (8 + bits_807X);
    arg0K1 = (1 + j_808X);
    arg0K2 = (x_810X + scalar_value_809X);
    goto L27803;}
  else {encode_scalar_valueUutf_8(scalar_value_809X, (((char *) 0)), 0, &out_of_spaceP_811X, &count_812X);
    arg0K0 = (encoding_length_805X + count_812X);
    arg0K1 = (1 + char_index_806X);
    goto L27794;}}
}
long s48_string_utf_8_length_n(long vm_string_813X, long start_index_814X, long count_815X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long count_827X;
  char out_of_spaceP_826X;
  long x_825X;
  long scalar_value_824X;
  long j_823X;
  long bits_822X;
  long char_index_821X;
  long encoding_length_820X;
  long max_819X;
  long v_818X;
  long max_817X;
  long v_816X;
 {  if ((3 == (3 & vm_string_813X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + vm_string_813X))))), 2))))) {
      goto L27825;}
    else {s48_argument_type_violation(vm_string_813X);
      goto L27825;}}
  else {s48_argument_type_violation(vm_string_813X);
    goto L27825;}}
 L27825: {
  v_816X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_813X))))), 8)) / 4;
  max_817X = -1 + v_816X;
  if ((start_index_814X < 0)) {
    goto L27851;}
  else {
    if ((max_817X < start_index_814X)) {
      goto L27851;}
    else {
      goto L27827;}}}
 L27851: {
s48_range_violation((PS_SHIFT_LEFT_INLINE(start_index_814X, 2)), 0, (PS_SHIFT_LEFT_INLINE(max_817X, 2)));
  goto L27827;}
 L27827: {
  v_818X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_813X))))), 8)) / 4;
  max_819X = v_818X - start_index_814X;
  if ((count_815X < 0)) {
    goto L27868;}
  else {
    if ((max_819X < count_815X)) {
      goto L27868;}
    else {
      goto L27831;}}}
 L27868: {
s48_range_violation((PS_SHIFT_LEFT_INLINE(count_815X, 2)), 0, (PS_SHIFT_LEFT_INLINE(max_819X, 2)));
  goto L27831;}
 L27831: {
  arg0K0 = 0;
  arg0K1 = 0;
  goto L27887;}
 L27887: {
  encoding_length_820X = arg0K0;
  char_index_821X = arg0K1;
  if ((char_index_821X < count_815X)) {
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = 0;
    goto L27896;}
  else {
    return encoding_length_820X;}}
 L27896: {
  bits_822X = arg0K0;
  j_823X = arg0K1;
  scalar_value_824X = arg0K2;
  if ((j_823X < 4)) {
    PS_SHIFT_LEFT((*((unsigned char *) ((((char *) (-3 + vm_string_813X))) + ((PS_SHIFT_LEFT_INLINE((start_index_814X + char_index_821X), 2)) + j_823X)))), bits_822X, x_825X)
    arg0K0 = (8 + bits_822X);
    arg0K1 = (1 + j_823X);
    arg0K2 = (x_825X + scalar_value_824X);
    goto L27896;}
  else {encode_scalar_valueUutf_8(scalar_value_824X, (((char *) 0)), 0, &out_of_spaceP_826X, &count_827X);
    arg0K0 = (encoding_length_820X + count_827X);
    arg0K1 = (1 + char_index_821X);
    goto L27887;}}
}
long s48_copy_string_to_utf_8(long vm_string_828X, char * string_829X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long count_838X;
  char out_of_spaceP_837X;
  long x_836X;
  long scalar_value_835X;
  long j_834X;
  long bits_833X;
  long target_index_832X;
  long source_index_831X;
  long count_830X;
 {  if ((3 == (3 & vm_string_828X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + vm_string_828X))))), 2))))) {
      goto L27925;}
    else {s48_argument_type_violation(vm_string_828X);
      goto L27925;}}
  else {s48_argument_type_violation(vm_string_828X);
    goto L27925;}}
 L27925: {
  count_830X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_828X))))), 8)) / 4;
  arg0K0 = 0;
  arg0K1 = 0;
  goto L27953;}
 L27953: {
  source_index_831X = arg0K0;
  target_index_832X = arg0K1;
  if ((source_index_831X < count_830X)) {
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = 0;
    goto L27962;}
  else {
    return target_index_832X;}}
 L27962: {
  bits_833X = arg0K0;
  j_834X = arg0K1;
  scalar_value_835X = arg0K2;
  if ((j_834X < 4)) {
    PS_SHIFT_LEFT((*((unsigned char *) ((((char *) (-3 + vm_string_828X))) + ((PS_SHIFT_LEFT_INLINE(source_index_831X, 2)) + j_834X)))), bits_833X, x_836X)
    arg0K0 = (8 + bits_833X);
    arg0K1 = (1 + j_834X);
    arg0K2 = (x_836X + scalar_value_835X);
    goto L27962;}
  else {encode_scalar_valueUutf_8(scalar_value_835X, (string_829X + target_index_832X), 4, &out_of_spaceP_837X, &count_838X);
    arg0K0 = (1 + source_index_831X);
    arg0K1 = (target_index_832X + count_838X);
    goto L27953;}}
}
long s48_copy_string_to_utf_8_n(long vm_string_839X, long start_840X, long count_841X, char * string_842X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long count_854X;
  char out_of_spaceP_853X;
  long x_852X;
  long scalar_value_851X;
  long j_850X;
  long bits_849X;
  long target_index_848X;
  long source_index_847X;
  long max_846X;
  long v_845X;
  long max_844X;
  long v_843X;
 {  if ((3 == (3 & vm_string_839X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + vm_string_839X))))), 2))))) {
      goto L27985;}
    else {s48_argument_type_violation(vm_string_839X);
      goto L27985;}}
  else {s48_argument_type_violation(vm_string_839X);
    goto L27985;}}
 L27985: {
  v_843X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_839X))))), 8)) / 4;
  max_844X = -1 + v_843X;
  if ((start_840X < 0)) {
    goto L28011;}
  else {
    if ((max_844X < start_840X)) {
      goto L28011;}
    else {
      goto L27987;}}}
 L28011: {
s48_range_violation((PS_SHIFT_LEFT_INLINE(start_840X, 2)), 0, (PS_SHIFT_LEFT_INLINE(max_844X, 2)));
  goto L27987;}
 L27987: {
  v_845X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_839X))))), 8)) / 4;
  max_846X = v_845X - start_840X;
  if ((count_841X < 0)) {
    goto L28028;}
  else {
    if ((max_846X < count_841X)) {
      goto L28028;}
    else {
      goto L27991;}}}
 L28028: {
s48_range_violation((PS_SHIFT_LEFT_INLINE(count_841X, 2)), 0, (PS_SHIFT_LEFT_INLINE(max_846X, 2)));
  goto L27991;}
 L27991: {
  arg0K0 = 0;
  arg0K1 = 0;
  goto L28048;}
 L28048: {
  source_index_847X = arg0K0;
  target_index_848X = arg0K1;
  if ((source_index_847X < count_841X)) {
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = 0;
    goto L28057;}
  else {
    return target_index_848X;}}
 L28057: {
  bits_849X = arg0K0;
  j_850X = arg0K1;
  scalar_value_851X = arg0K2;
  if ((j_850X < 4)) {
    PS_SHIFT_LEFT((*((unsigned char *) ((((char *) (-3 + vm_string_839X))) + ((PS_SHIFT_LEFT_INLINE((start_840X + source_index_847X), 2)) + j_850X)))), bits_849X, x_852X)
    arg0K0 = (8 + bits_849X);
    arg0K1 = (1 + j_850X);
    arg0K2 = (x_852X + scalar_value_851X);
    goto L28057;}
  else {encode_scalar_valueUutf_8(scalar_value_851X, (string_842X + target_index_848X), 4, &out_of_spaceP_853X, &count_854X);
    arg0K0 = (1 + source_index_847X);
    arg0K1 = (target_index_848X + count_854X);
    goto L28048;}}
}
long s48_string_utf_16be_length(long vm_string_855X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long count_864X;
  char out_of_spaceP_863X;
  long x_862X;
  long scalar_value_861X;
  long j_860X;
  long bits_859X;
  long char_index_858X;
  long encoding_length_857X;
  long count_856X;
 {  if ((3 == (3 & vm_string_855X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + vm_string_855X))))), 2))))) {
      goto L28085;}
    else {s48_argument_type_violation(vm_string_855X);
      goto L28085;}}
  else {s48_argument_type_violation(vm_string_855X);
    goto L28085;}}
 L28085: {
  count_856X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_855X))))), 8)) / 4;
  arg0K0 = 0;
  arg0K1 = 0;
  goto L28112;}
 L28112: {
  encoding_length_857X = arg0K0;
  char_index_858X = arg0K1;
  if ((char_index_858X < count_856X)) {
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = 0;
    goto L28121;}
  else {
    return (encoding_length_857X / 2);}}
 L28121: {
  bits_859X = arg0K0;
  j_860X = arg0K1;
  scalar_value_861X = arg0K2;
  if ((j_860X < 4)) {
    PS_SHIFT_LEFT((*((unsigned char *) ((((char *) (-3 + vm_string_855X))) + ((PS_SHIFT_LEFT_INLINE(char_index_858X, 2)) + j_860X)))), bits_859X, x_862X)
    arg0K0 = (8 + bits_859X);
    arg0K1 = (1 + j_860X);
    arg0K2 = (x_862X + scalar_value_861X);
    goto L28121;}
  else {encode_scalar_valueUutf_16be(scalar_value_861X, (((char *) 0)), 0, &out_of_spaceP_863X, &count_864X);
    arg0K0 = (encoding_length_857X + count_864X);
    arg0K1 = (1 + char_index_858X);
    goto L28112;}}
}
long s48_string_utf_16be_length_n(long vm_string_865X, long start_index_866X, long count_867X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long count_879X;
  char out_of_spaceP_878X;
  long x_877X;
  long scalar_value_876X;
  long j_875X;
  long bits_874X;
  long char_index_873X;
  long encoding_length_872X;
  long max_871X;
  long v_870X;
  long max_869X;
  long v_868X;
 {  if ((3 == (3 & vm_string_865X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + vm_string_865X))))), 2))))) {
      goto L28143;}
    else {s48_argument_type_violation(vm_string_865X);
      goto L28143;}}
  else {s48_argument_type_violation(vm_string_865X);
    goto L28143;}}
 L28143: {
  v_868X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_865X))))), 8)) / 4;
  max_869X = -1 + v_868X;
  if ((start_index_866X < 0)) {
    goto L28169;}
  else {
    if ((max_869X < start_index_866X)) {
      goto L28169;}
    else {
      goto L28145;}}}
 L28169: {
s48_range_violation((PS_SHIFT_LEFT_INLINE(start_index_866X, 2)), 0, (PS_SHIFT_LEFT_INLINE(max_869X, 2)));
  goto L28145;}
 L28145: {
  v_870X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_865X))))), 8)) / 4;
  max_871X = v_870X - start_index_866X;
  if ((count_867X < 0)) {
    goto L28186;}
  else {
    if ((max_871X < count_867X)) {
      goto L28186;}
    else {
      goto L28149;}}}
 L28186: {
s48_range_violation((PS_SHIFT_LEFT_INLINE(count_867X, 2)), 0, (PS_SHIFT_LEFT_INLINE(max_871X, 2)));
  goto L28149;}
 L28149: {
  arg0K0 = 0;
  arg0K1 = 0;
  goto L28205;}
 L28205: {
  encoding_length_872X = arg0K0;
  char_index_873X = arg0K1;
  if ((char_index_873X < count_867X)) {
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = 0;
    goto L28214;}
  else {
    return (encoding_length_872X / 2);}}
 L28214: {
  bits_874X = arg0K0;
  j_875X = arg0K1;
  scalar_value_876X = arg0K2;
  if ((j_875X < 4)) {
    PS_SHIFT_LEFT((*((unsigned char *) ((((char *) (-3 + vm_string_865X))) + ((PS_SHIFT_LEFT_INLINE((start_index_866X + char_index_873X), 2)) + j_875X)))), bits_874X, x_877X)
    arg0K0 = (8 + bits_874X);
    arg0K1 = (1 + j_875X);
    arg0K2 = (x_877X + scalar_value_876X);
    goto L28214;}
  else {encode_scalar_valueUutf_16be(scalar_value_876X, (((char *) 0)), 0, &out_of_spaceP_878X, &count_879X);
    arg0K0 = (encoding_length_872X + count_879X);
    arg0K1 = (1 + char_index_873X);
    goto L28205;}}
}
long s48_copy_string_to_utf_16beU(long vm_string_880X, char * string_881X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long count_890X;
  char out_of_spaceP_889X;
  long x_888X;
  long scalar_value_887X;
  long j_886X;
  long bits_885X;
  long target_index_884X;
  long source_index_883X;
  long count_882X;
 {  if ((3 == (3 & vm_string_880X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + vm_string_880X))))), 2))))) {
      goto L28243;}
    else {s48_argument_type_violation(vm_string_880X);
      goto L28243;}}
  else {s48_argument_type_violation(vm_string_880X);
    goto L28243;}}
 L28243: {
  count_882X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_880X))))), 8)) / 4;
  arg0K0 = 0;
  arg0K1 = 0;
  goto L28271;}
 L28271: {
  source_index_883X = arg0K0;
  target_index_884X = arg0K1;
  if ((source_index_883X < count_882X)) {
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = 0;
    goto L28280;}
  else {
    return (target_index_884X / 2);}}
 L28280: {
  bits_885X = arg0K0;
  j_886X = arg0K1;
  scalar_value_887X = arg0K2;
  if ((j_886X < 4)) {
    PS_SHIFT_LEFT((*((unsigned char *) ((((char *) (-3 + vm_string_880X))) + ((PS_SHIFT_LEFT_INLINE(source_index_883X, 2)) + j_886X)))), bits_885X, x_888X)
    arg0K0 = (8 + bits_885X);
    arg0K1 = (1 + j_886X);
    arg0K2 = (x_888X + scalar_value_887X);
    goto L28280;}
  else {encode_scalar_valueUutf_16be(scalar_value_887X, (string_881X + target_index_884X), 4, &out_of_spaceP_889X, &count_890X);
    arg0K0 = (1 + source_index_883X);
    arg0K1 = (target_index_884X + count_890X);
    goto L28271;}}
}
long s48_copy_string_to_utf_16be_nU(long vm_string_891X, long start_892X, long count_893X, char * string_894X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long count_906X;
  char out_of_spaceP_905X;
  long x_904X;
  long scalar_value_903X;
  long j_902X;
  long bits_901X;
  long target_index_900X;
  long source_index_899X;
  long max_898X;
  long v_897X;
  long max_896X;
  long v_895X;
 {  if ((3 == (3 & vm_string_891X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + vm_string_891X))))), 2))))) {
      goto L28303;}
    else {s48_argument_type_violation(vm_string_891X);
      goto L28303;}}
  else {s48_argument_type_violation(vm_string_891X);
    goto L28303;}}
 L28303: {
  v_895X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_891X))))), 8)) / 4;
  max_896X = -1 + v_895X;
  if ((start_892X < 0)) {
    goto L28329;}
  else {
    if ((max_896X < start_892X)) {
      goto L28329;}
    else {
      goto L28305;}}}
 L28329: {
s48_range_violation((PS_SHIFT_LEFT_INLINE(start_892X, 2)), 0, (PS_SHIFT_LEFT_INLINE(max_896X, 2)));
  goto L28305;}
 L28305: {
  v_897X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_891X))))), 8)) / 4;
  max_898X = v_897X - start_892X;
  if ((count_893X < 0)) {
    goto L28346;}
  else {
    if ((max_898X < count_893X)) {
      goto L28346;}
    else {
      goto L28309;}}}
 L28346: {
s48_range_violation((PS_SHIFT_LEFT_INLINE(count_893X, 2)), 0, (PS_SHIFT_LEFT_INLINE(max_898X, 2)));
  goto L28309;}
 L28309: {
  arg0K0 = 0;
  arg0K1 = 0;
  goto L28366;}
 L28366: {
  source_index_899X = arg0K0;
  target_index_900X = arg0K1;
  if ((source_index_899X < count_893X)) {
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = 0;
    goto L28375;}
  else {
    return (target_index_900X / 2);}}
 L28375: {
  bits_901X = arg0K0;
  j_902X = arg0K1;
  scalar_value_903X = arg0K2;
  if ((j_902X < 4)) {
    PS_SHIFT_LEFT((*((unsigned char *) ((((char *) (-3 + vm_string_891X))) + ((PS_SHIFT_LEFT_INLINE((start_892X + source_index_899X), 2)) + j_902X)))), bits_901X, x_904X)
    arg0K0 = (8 + bits_901X);
    arg0K1 = (1 + j_902X);
    arg0K2 = (x_904X + scalar_value_903X);
    goto L28375;}
  else {encode_scalar_valueUutf_16be(scalar_value_903X, (string_894X + target_index_900X), 4, &out_of_spaceP_905X, &count_906X);
    arg0K0 = (1 + source_index_899X);
    arg0K1 = (target_index_900X + count_906X);
    goto L28366;}}
}
long s48_string_utf_16le_length(long vm_string_907X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long count_916X;
  char out_of_spaceP_915X;
  long x_914X;
  long scalar_value_913X;
  long j_912X;
  long bits_911X;
  long char_index_910X;
  long encoding_length_909X;
  long count_908X;
 {  if ((3 == (3 & vm_string_907X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + vm_string_907X))))), 2))))) {
      goto L28403;}
    else {s48_argument_type_violation(vm_string_907X);
      goto L28403;}}
  else {s48_argument_type_violation(vm_string_907X);
    goto L28403;}}
 L28403: {
  count_908X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_907X))))), 8)) / 4;
  arg0K0 = 0;
  arg0K1 = 0;
  goto L28430;}
 L28430: {
  encoding_length_909X = arg0K0;
  char_index_910X = arg0K1;
  if ((char_index_910X < count_908X)) {
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = 0;
    goto L28439;}
  else {
    return (encoding_length_909X / 2);}}
 L28439: {
  bits_911X = arg0K0;
  j_912X = arg0K1;
  scalar_value_913X = arg0K2;
  if ((j_912X < 4)) {
    PS_SHIFT_LEFT((*((unsigned char *) ((((char *) (-3 + vm_string_907X))) + ((PS_SHIFT_LEFT_INLINE(char_index_910X, 2)) + j_912X)))), bits_911X, x_914X)
    arg0K0 = (8 + bits_911X);
    arg0K1 = (1 + j_912X);
    arg0K2 = (x_914X + scalar_value_913X);
    goto L28439;}
  else {encode_scalar_valueUutf_16le(scalar_value_913X, (((char *) 0)), 0, &out_of_spaceP_915X, &count_916X);
    arg0K0 = (encoding_length_909X + count_916X);
    arg0K1 = (1 + char_index_910X);
    goto L28430;}}
}
long s48_string_utf_16le_length_n(long vm_string_917X, long start_index_918X, long count_919X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long count_931X;
  char out_of_spaceP_930X;
  long x_929X;
  long scalar_value_928X;
  long j_927X;
  long bits_926X;
  long char_index_925X;
  long encoding_length_924X;
  long max_923X;
  long v_922X;
  long max_921X;
  long v_920X;
 {  if ((3 == (3 & vm_string_917X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + vm_string_917X))))), 2))))) {
      goto L28461;}
    else {s48_argument_type_violation(vm_string_917X);
      goto L28461;}}
  else {s48_argument_type_violation(vm_string_917X);
    goto L28461;}}
 L28461: {
  v_920X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_917X))))), 8)) / 4;
  max_921X = -1 + v_920X;
  if ((start_index_918X < 0)) {
    goto L28487;}
  else {
    if ((max_921X < start_index_918X)) {
      goto L28487;}
    else {
      goto L28463;}}}
 L28487: {
s48_range_violation((PS_SHIFT_LEFT_INLINE(start_index_918X, 2)), 0, (PS_SHIFT_LEFT_INLINE(max_921X, 2)));
  goto L28463;}
 L28463: {
  v_922X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_917X))))), 8)) / 4;
  max_923X = v_922X - start_index_918X;
  if ((count_919X < 0)) {
    goto L28504;}
  else {
    if ((max_923X < count_919X)) {
      goto L28504;}
    else {
      goto L28467;}}}
 L28504: {
s48_range_violation((PS_SHIFT_LEFT_INLINE(count_919X, 2)), 0, (PS_SHIFT_LEFT_INLINE(max_923X, 2)));
  goto L28467;}
 L28467: {
  arg0K0 = 0;
  arg0K1 = 0;
  goto L28523;}
 L28523: {
  encoding_length_924X = arg0K0;
  char_index_925X = arg0K1;
  if ((char_index_925X < count_919X)) {
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = 0;
    goto L28532;}
  else {
    return (encoding_length_924X / 2);}}
 L28532: {
  bits_926X = arg0K0;
  j_927X = arg0K1;
  scalar_value_928X = arg0K2;
  if ((j_927X < 4)) {
    PS_SHIFT_LEFT((*((unsigned char *) ((((char *) (-3 + vm_string_917X))) + ((PS_SHIFT_LEFT_INLINE((start_index_918X + char_index_925X), 2)) + j_927X)))), bits_926X, x_929X)
    arg0K0 = (8 + bits_926X);
    arg0K1 = (1 + j_927X);
    arg0K2 = (x_929X + scalar_value_928X);
    goto L28532;}
  else {encode_scalar_valueUutf_16le(scalar_value_928X, (((char *) 0)), 0, &out_of_spaceP_930X, &count_931X);
    arg0K0 = (encoding_length_924X + count_931X);
    arg0K1 = (1 + char_index_925X);
    goto L28523;}}
}
long s48_copy_string_to_utf_16leU(long vm_string_932X, char * string_933X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long count_942X;
  char out_of_spaceP_941X;
  long x_940X;
  long scalar_value_939X;
  long j_938X;
  long bits_937X;
  long target_index_936X;
  long source_index_935X;
  long count_934X;
 {  if ((3 == (3 & vm_string_932X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + vm_string_932X))))), 2))))) {
      goto L28561;}
    else {s48_argument_type_violation(vm_string_932X);
      goto L28561;}}
  else {s48_argument_type_violation(vm_string_932X);
    goto L28561;}}
 L28561: {
  count_934X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_932X))))), 8)) / 4;
  arg0K0 = 0;
  arg0K1 = 0;
  goto L28589;}
 L28589: {
  source_index_935X = arg0K0;
  target_index_936X = arg0K1;
  if ((source_index_935X < count_934X)) {
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = 0;
    goto L28598;}
  else {
    return (target_index_936X / 2);}}
 L28598: {
  bits_937X = arg0K0;
  j_938X = arg0K1;
  scalar_value_939X = arg0K2;
  if ((j_938X < 4)) {
    PS_SHIFT_LEFT((*((unsigned char *) ((((char *) (-3 + vm_string_932X))) + ((PS_SHIFT_LEFT_INLINE(source_index_935X, 2)) + j_938X)))), bits_937X, x_940X)
    arg0K0 = (8 + bits_937X);
    arg0K1 = (1 + j_938X);
    arg0K2 = (x_940X + scalar_value_939X);
    goto L28598;}
  else {encode_scalar_valueUutf_16le(scalar_value_939X, (string_933X + target_index_936X), 4, &out_of_spaceP_941X, &count_942X);
    arg0K0 = (1 + source_index_935X);
    arg0K1 = (target_index_936X + count_942X);
    goto L28589;}}
}
long s48_copy_string_to_utf_16le_nU(long vm_string_943X, long start_944X, long count_945X, char * string_946X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long count_958X;
  char out_of_spaceP_957X;
  long x_956X;
  long scalar_value_955X;
  long j_954X;
  long bits_953X;
  long target_index_952X;
  long source_index_951X;
  long max_950X;
  long v_949X;
  long max_948X;
  long v_947X;
 {  if ((3 == (3 & vm_string_943X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + vm_string_943X))))), 2))))) {
      goto L28621;}
    else {s48_argument_type_violation(vm_string_943X);
      goto L28621;}}
  else {s48_argument_type_violation(vm_string_943X);
    goto L28621;}}
 L28621: {
  v_947X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_943X))))), 8)) / 4;
  max_948X = -1 + v_947X;
  if ((start_944X < 0)) {
    goto L28647;}
  else {
    if ((max_948X < start_944X)) {
      goto L28647;}
    else {
      goto L28623;}}}
 L28647: {
s48_range_violation((PS_SHIFT_LEFT_INLINE(start_944X, 2)), 0, (PS_SHIFT_LEFT_INLINE(max_948X, 2)));
  goto L28623;}
 L28623: {
  v_949X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + vm_string_943X))))), 8)) / 4;
  max_950X = v_949X - start_944X;
  if ((count_945X < 0)) {
    goto L28664;}
  else {
    if ((max_950X < count_945X)) {
      goto L28664;}
    else {
      goto L28627;}}}
 L28664: {
s48_range_violation((PS_SHIFT_LEFT_INLINE(count_945X, 2)), 0, (PS_SHIFT_LEFT_INLINE(max_950X, 2)));
  goto L28627;}
 L28627: {
  arg0K0 = 0;
  arg0K1 = 0;
  goto L28684;}
 L28684: {
  source_index_951X = arg0K0;
  target_index_952X = arg0K1;
  if ((source_index_951X < count_945X)) {
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = 0;
    goto L28693;}
  else {
    return (target_index_952X / 2);}}
 L28693: {
  bits_953X = arg0K0;
  j_954X = arg0K1;
  scalar_value_955X = arg0K2;
  if ((j_954X < 4)) {
    PS_SHIFT_LEFT((*((unsigned char *) ((((char *) (-3 + vm_string_943X))) + ((PS_SHIFT_LEFT_INLINE((start_944X + source_index_951X), 2)) + j_954X)))), bits_953X, x_956X)
    arg0K0 = (8 + bits_953X);
    arg0K1 = (1 + j_954X);
    arg0K2 = (x_956X + scalar_value_955X);
    goto L28693;}
  else {encode_scalar_valueUutf_16le(scalar_value_955X, (string_946X + target_index_952X), 4, &out_of_spaceP_957X, &count_958X);
    arg0K0 = (1 + source_index_951X);
    arg0K1 = (target_index_952X + count_958X);
    goto L28684;}}
}
void check_stack(void)
{
  char * arg3K0;
  char * arg3K1;
  long arg0K0;
  long v_981X;
  char x_980X;
  long x_979X;
  char * ptr_978X;
  long mask_977X;
  long size_976X;
  char * pointer_975X;
  char x_974X;
  long x_973X;
  char * addr_972X;
  char * trace_ptr_971X;
  char * mask_ptr_970X;
  long v_969X;
  char * mask_pointer_968X;
  long size_967X;
  char * pointer_966X;
  char * contents_pointer_965X;
  long mask_size_964X;
  char * code_pointer_963X;
  char * cont_962X;
  char x_961X;
  long x_960X;
  char * index_959X;
 {  arg3K0 = (SstackS);
  goto L28808;}
 L28808: {
  index_959X = arg3K0;
  if ((index_959X < ((SstackS) + (-8 & ((ScontS) - (SstackS)))))) {
    x_960X = *((long *) index_959X);
    if ((2 == (3 & x_960X))) {
      goto L28870;}
    else {
      if ((3 == (3 & x_960X))) {
        x_961X = s48_stob_in_heapP(x_960X);
        if (x_961X) {
          goto L28817;}
        else {
          goto L28870;}}
      else {
        goto L28817;}}}
  else {
    arg3K0 = (ScontS);
    goto L28912;}}
 L28870: {
  ps_write_string("bad descriptor in stack", (stderr));
  ps_write_integer(x_960X, (stderr));
  ps_write_integer((*((long *) (((char *) 0)))), (stderr));
  goto L28817;}
 L28817: {
  arg3K0 = (index_959X + 8);
  goto L28808;}
 L28912: {
  cont_962X = arg3K0;
  if ((cont_962X == (Sbottom_of_stackS))) {
    return;}
  else {
    code_pointer_963X = ((char *) (*((long *) cont_962X)));
    mask_size_964X = *((unsigned char *) (code_pointer_963X + -3));
    contents_pointer_965X = cont_962X + 8;
    if ((0 == mask_size_964X)) {
      pointer_966X = (((char *) (*((long *) cont_962X)))) + -2;
      size_967X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) pointer_966X)), 8)) + (*((unsigned char *) (pointer_966X + 1)));
      if ((65535 == size_967X)) {
        arg0K0 = (PS_SHIFT_RIGHT_INLINE((*((long *) (cont_962X + 8))), 2));
        goto L21410;}
      else {
        arg0K0 = size_967X;
        goto L21410;}}
    else {
      mask_pointer_968X = code_pointer_963X + -7;
      arg3K0 = (mask_pointer_968X + (0 - mask_size_964X));
      arg3K1 = contents_pointer_965X;
      goto L8845;}}}
 L21410: {
  v_969X = arg0K0;
  arg3K0 = contents_pointer_965X;
  goto L8786;}
 L8845: {
  mask_ptr_970X = arg3K0;
  trace_ptr_971X = arg3K1;
  if ((mask_ptr_970X == mask_pointer_968X)) {
    goto L24389;}
  else {
    arg0K0 = (*((unsigned char *) mask_ptr_970X));
    arg3K1 = trace_ptr_971X;
    goto L8853;}}
 L8786: {
  addr_972X = arg3K0;
  if ((addr_972X < (cont_962X + (8 + (PS_SHIFT_LEFT_INLINE(v_969X, 3)))))) {
    x_973X = *((long *) addr_972X);
    if ((2 == (3 & x_973X))) {
      goto L8804;}
    else {
      if ((3 == (3 & x_973X))) {
        x_974X = s48_stob_in_heapP(x_973X);
        if (x_974X) {
          goto L8791;}
        else {
          goto L8804;}}
      else {
        goto L8791;}}}
  else {
    goto L24389;}}
 L24389: {
  pointer_975X = (((char *) (*((long *) cont_962X)))) + -2;
  size_976X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) pointer_975X)), 8)) + (*((unsigned char *) (pointer_975X + 1)));
  if ((65535 == size_976X)) {
    arg0K0 = (PS_SHIFT_RIGHT_INLINE((*((long *) (cont_962X + 8))), 2));
    goto L24394;}
  else {
    arg0K0 = size_976X;
    goto L24394;}}
 L8853: {
  mask_977X = arg0K0;
  ptr_978X = arg3K1;
  if ((0 == mask_977X)) {
    arg3K0 = (mask_ptr_970X + 1);
    arg3K1 = (trace_ptr_971X + 64);
    goto L8845;}
  else {
    if ((1 == (1 & mask_977X))) {
      x_979X = *((long *) ptr_978X);
      if ((2 == (3 & x_979X))) {
        goto L8910;}
      else {
        if ((3 == (3 & x_979X))) {
          x_980X = s48_stob_in_heapP(x_979X);
          if (x_980X) {
            goto L8869;}
          else {
            goto L8910;}}
        else {
          goto L8869;}}}
    else {
      goto L8869;}}}
 L8804: {
  ps_write_string("bad descriptor in stack", (stderr));
  ps_write_integer(x_973X, (stderr));
  ps_write_integer((*((long *) (((char *) 0)))), (stderr));
  goto L8791;}
 L8791: {
  arg3K0 = (addr_972X + 8);
  goto L8786;}
 L24394: {
  v_981X = arg0K0;
  arg3K0 = (cont_962X + (8 + (PS_SHIFT_LEFT_INLINE(v_981X, 3))));
  goto L28912;}
 L8910: {
  ps_write_string("bad descriptor in stack", (stderr));
  ps_write_integer(x_979X, (stderr));
  ps_write_integer((*((long *) (((char *) 0)))), (stderr));
  goto L8869;}
 L8869: {
  arg0K0 = (PS_SHIFT_RIGHT_INLINE(mask_977X, 1));
  arg3K1 = (ptr_978X + 8);
  goto L8853;}
}
long s48_really_add_channel(long mode_982X, long id_983X, long os_index_984X)
{
  long arg0K1;
  long arg0K0;
  long status_989X;
  long channel_988X;
  long channel_987X;
  char x_986X;
  char temp_985X;
 {s48_make_availableAgc(64);
  temp_985X = os_index_984X < (Snumber_of_channelsS);
  if (temp_985X) {
    goto L28977;}
  else {
    x_986X = add_more_channels(os_index_984X);
    if (x_986X) {
      goto L28977;}
    else {
      arg0K0 = 1;
      arg0K1 = 10;
      goto L28951;}}}
 L28977: {
  if ((1 == (*((Svm_channelsS) + os_index_984X)))) {
    channel_987X = make_channel((-4 & mode_982X), id_983X, (PS_SHIFT_LEFT_INLINE(os_index_984X, 2)), 1, 1, 1, 1, 0);
    *((Svm_channelsS) + os_index_984X) = channel_987X;
    arg0K0 = channel_987X;
    arg0K1 = 10;
    goto L28951;}
  else {
    arg0K0 = 1;
    arg0K1 = 12;
    goto L28951;}}
 L28951: {
  channel_988X = arg0K0;
  status_989X = arg0K1;
  if ((3 == (3 & channel_988X))) {
    if ((6 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + channel_988X))))), 2))))) {
      return channel_988X;}
    else {
      goto L28959;}}
  else {
    goto L28959;}}
 L28959: {
  return (PS_SHIFT_LEFT_INLINE(status_989X, 2));}
}
long s48_enter_string_latin_1(char *s_990X)
{

 {  return enter_stringAgc_n(s_990X, (strlen((char *) s_990X)));}
}
long s48_integer_bit_count(long x_991X)
{

 {  return integer_bit_count(x_991X);}
}
long s48_enter_integer(long x_992X)
{
  char * v_993X;
 {s48_make_availableAgc(24);
  if ((2305843009213693951 < x_992X)) {
    goto L29834;}
  else {
    if ((x_992X < -2305843009213693952)) {
      goto L29834;}
    else {
      return (PS_SHIFT_LEFT_INLINE(x_992X, 2));}}}
 L29834: {
  v_993X = (char *) s48_long_to_bignum(x_992X);
  return enter_bignum(v_993X);}
}
long s48_enter_unsigned_integer(unsigned long x_994X)
{
  char * v_995X;
 {s48_make_availableAgc(24);
  if (((((unsigned long) 2305843009213693951)) < x_994X)) {
    v_995X = (char *) s48_ulong_to_bignum(x_994X);
    return enter_bignum(v_995X);}
  else {
    return (PS_SHIFT_LEFT_INLINE((((long) x_994X)), 2));}}
}
long s48_integer_or_floanum_add(long x_996X, long y_997X)
{
  long Kdouble_1003X;
  char * addr_1002X;
  double y_1001X;
  long value_1000X;
  double x_999X;
  long value_998X;
 {  if ((3 == (3 & x_996X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + x_996X))))), 2))))) {
      Stemp0S = x_996X;
      Stemp1S = y_997X;s48_make_availableAgc(16);
      value_998X = Stemp0S;
      Stemp0S = 1;
      x_999X = *((double *) (((char *) (-3 + value_998X))));
      value_1000X = Stemp1S;
      Stemp1S = 1;
      y_1001X = *((double *) (((char *) (-3 + value_1000X))));
      addr_1002X = s48_allocate_small(16);
      *((long *) addr_1002X) = (long) (2122);
      Kdouble_1003X = 3 + (((long) (addr_1002X + 8)));
      *((double *) (((char *) (-3 + Kdouble_1003X)))) = (double) ((x_999X + y_1001X));
      return Kdouble_1003X;}
    else {
      return integer_add(x_996X, y_997X);}}
  else {
    return integer_add(x_996X, y_997X);}}
}
long s48_integer_or_floanum_sub(long x_1004X, long y_1005X)
{
  long Kdouble_1011X;
  char * addr_1010X;
  double y_1009X;
  long value_1008X;
  double x_1007X;
  long value_1006X;
 {  if ((3 == (3 & x_1004X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + x_1004X))))), 2))))) {
      Stemp0S = x_1004X;
      Stemp1S = y_1005X;s48_make_availableAgc(16);
      value_1006X = Stemp0S;
      Stemp0S = 1;
      x_1007X = *((double *) (((char *) (-3 + value_1006X))));
      value_1008X = Stemp1S;
      Stemp1S = 1;
      y_1009X = *((double *) (((char *) (-3 + value_1008X))));
      addr_1010X = s48_allocate_small(16);
      *((long *) addr_1010X) = (long) (2122);
      Kdouble_1011X = 3 + (((long) (addr_1010X + 8)));
      *((double *) (((char *) (-3 + Kdouble_1011X)))) = (double) ((x_1007X - y_1009X));
      return Kdouble_1011X;}
    else {
      return integer_subtract(x_1004X, y_1005X);}}
  else {
    return integer_subtract(x_1004X, y_1005X);}}
}
long s48_integer_or_floanum_mul(long x_1012X, long y_1013X)
{
  long Kdouble_1019X;
  char * addr_1018X;
  double y_1017X;
  long value_1016X;
  double x_1015X;
  long value_1014X;
 {  if ((3 == (3 & x_1012X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + x_1012X))))), 2))))) {
      Stemp0S = x_1012X;
      Stemp1S = y_1013X;s48_make_availableAgc(16);
      value_1014X = Stemp0S;
      Stemp0S = 1;
      x_1015X = *((double *) (((char *) (-3 + value_1014X))));
      value_1016X = Stemp1S;
      Stemp1S = 1;
      y_1017X = *((double *) (((char *) (-3 + value_1016X))));
      addr_1018X = s48_allocate_small(16);
      *((long *) addr_1018X) = (long) (2122);
      Kdouble_1019X = 3 + (((long) (addr_1018X + 8)));
      *((double *) (((char *) (-3 + Kdouble_1019X)))) = (double) ((x_1015X * y_1017X));
      return Kdouble_1019X;}
    else {
      return integer_multiply(x_1012X, y_1013X);}}
  else {
    return integer_multiply(x_1012X, y_1013X);}}
}
char s48_integer_divide(long x_1020X, long y_1021X, long *TT0, long *TT1, long *TT2, long *TT3)
{

 {  return integer_divide(x_1020X, y_1021X, TT0, TT1, TT2, TT3);}
}
long s48_integer_bitwise_not(long x_1022X)
{

 {  return integer_bitwise_not(x_1022X);}
}
long s48_integer_bitwise_and(long x_1023X, long y_1024X)
{

 {  return integer_bitwise_and(x_1023X, y_1024X);}
}
long s48_integer_bitwise_ior(long x_1025X, long y_1026X)
{

 {  return integer_bitwise_ior(x_1025X, y_1026X);}
}
long s48_integer_bitwise_xor(long x_1027X, long y_1028X)
{

 {  return integer_bitwise_xor(x_1027X, y_1028X);}
}
void s48_setup_external_exception(long why_1029X, long nargs_1030X)
{

 {push_exception_setupB(why_1029X, 1);
  if ((10 < nargs_1030X)) {
    ps_error("too many arguments from external exception", 0);
    goto L30902;}
  else {
    goto L30902;}}
 L30902: {
  Sexternal_exception_nargsS = nargs_1030X;
  Sexternal_exceptionPS = 1;
  return;}
}
long message_element(long thing_1031X, FILE * out_1032X)
{
  char *arg5K0;
  char *v_1036X;
  long v_1035X;
  char x_1034X;
  long v_1033X;
 {  if ((0 == (3 & thing_1031X))) {
    return (ps_write_integer((PS_SHIFT_RIGHT_INLINE(thing_1031X, 2)), out_1032X));}
  else {
    if ((9 == (255 & thing_1031X))) {
      ps_write_string("#\\", out_1032X);
      PS_WRITE_CHAR((((char) (PS_SHIFT_RIGHT_INLINE(thing_1031X, 8)))), out_1032X, v_1033X)
      return v_1033X;}
    else {
      if ((3 == (3 & thing_1031X))) {
        if ((9 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + thing_1031X))))), 2))))) {
          if ((0 < (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + thing_1031X))))), 8))), 3)))) {
            x_1034X = not_record_typeP((*((long *) (((char *) (-3 + thing_1031X))))));
            if (x_1034X) {
              goto L30943;}
            else {
              ps_write_string("#{", out_1032X);write_vm_string((*((long *) (((char *) (-3 + (*((long *) ((((char *) (-3 + (*((long *) (((char *) (-3 + thing_1031X)))))))) + 24)))))))), out_1032X);
              PS_WRITE_CHAR(125, out_1032X, v_1035X)
              return v_1035X;}}
          else {
            goto L30943;}}
        else {
          goto L30943;}}
      else {
        goto L30943;}}}}
 L30943: {
  if ((3 == (3 & thing_1031X))) {
    if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + thing_1031X))))), 2))))) {
      return write_vm_string(thing_1031X, out_1032X);}
    else {
      goto L30947;}}
  else {
    goto L30947;}}
 L30947: {
  if ((3 == (3 & thing_1031X))) {
    if ((1 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + thing_1031X))))), 2))))) {
      return write_vm_string((*((long *) (((char *) (-3 + thing_1031X))))), out_1032X);}
    else {
      goto L30953;}}
  else {
    goto L30953;}}
 L30953: {
  if ((1 == thing_1031X)) {
    goto L30958;}
  else {
    if ((5 == thing_1031X)) {
      goto L30958;}
    else {
      if ((25 == thing_1031X)) {
        arg5K0 = "()";
        goto L30997;}
      else {
        if ((3 == (3 & thing_1031X))) {
          if ((0 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + thing_1031X))))), 2))))) {
            arg5K0 = "(...)";
            goto L30997;}
          else {
            goto L30971;}}
        else {
          goto L30971;}}}}}
 L30958: {
  if ((1 == thing_1031X)) {
    arg5K0 = "#f";
    goto L30997;}
  else {
    arg5K0 = "#t";
    goto L30997;}}
 L30997: {
  v_1036X = arg5K0;
  return (ps_write_string(v_1036X, out_1032X));}
 L30971: {
  if ((3 == (3 & thing_1031X))) {
    if ((2 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + thing_1031X))))), 2))))) {
      arg5K0 = "#(...)";
      goto L30997;}
    else {
      goto L30975;}}
  else {
    goto L30975;}}
 L30975: {
  if ((3 == (3 & thing_1031X))) {
    if ((3 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + thing_1031X))))), 2))))) {
      arg5K0 = "#{procedure}";
      goto L30997;}
    else {
      goto L30979;}}
  else {
    goto L30979;}}
 L30979: {
  if ((3 == (3 & thing_1031X))) {
    if ((12 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + thing_1031X))))), 2))))) {
      arg5K0 = "#{template}";
      goto L30997;}
    else {
      goto L30983;}}
  else {
    goto L30983;}}
 L30983: {
  if ((3 == (3 & thing_1031X))) {
    if ((4 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + thing_1031X))))), 2))))) {
      arg5K0 = "#{location}";
      goto L30997;}
    else {
      goto L30987;}}
  else {
    goto L30987;}}
 L30987: {
  if ((3 == (3 & thing_1031X))) {
    if ((17 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + thing_1031X))))), 2))))) {
      arg5K0 = "#{code-vector}";
      goto L30997;}
    else {
      goto L30991;}}
  else {
    goto L30991;}}
 L30991: {
  if ((3 == (3 & thing_1031X))) {
    if ((10 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + thing_1031X))))), 2))))) {
      arg5K0 = "#{continuation}";
      goto L30997;}
    else {
      arg5K0 = "???";
      goto L30997;}}
  else {
    arg5K0 = "???";
    goto L30997;}}
}
long s48_integer_quotient(long x_1037X, long y_1038X)
{

 {  return Hinteger_op8731(x_1037X, y_1038X);}
}
long s48_integer_remainder(long x_1039X, long y_1040X)
{

 {  return Hinteger_op8662(x_1039X, y_1040X);}
}
void s48_copy_stack_into_heap(void)
{
  char * arg3K1;
  char * arg3K0;
  char * arg_1044X;
  char * loc_1043X;
  char * top_1042X;
  long arg_count_1041X;
 {s48_make_availableAgc((PS_SHIFT_LEFT_INLINE((-4 & (PS_SHIFT_RIGHT_INLINE(((Sstack_endS) - (SstackS)), 1))), 3)));
  arg_count_1041X = PS_SHIFT_RIGHT_INLINE(((ScontS) - (SstackS)), 3);
  top_1042X = SstackS;
  if ((1 == (((long) (ScontS))))) {
    goto L31350;}
  else {really_preserve_continuation(0);
    goto L31350;}}
 L31350: {
  SstackS = (ScontS);
  arg3K0 = ((SstackS) + -8);
  arg3K1 = (top_1042X + (-8 + (PS_SHIFT_LEFT_INLINE(arg_count_1041X, 3))));
  goto L31379;}
 L31379: {
  loc_1043X = arg3K0;
  arg_1044X = arg3K1;
  if ((arg_1044X < top_1042X)) {
    SstackS = ((SstackS) + (0 - (PS_SHIFT_LEFT_INLINE(arg_count_1041X, 3))));
    return;}
  else {
    *((long *) loc_1043X) = (long) ((*((long *) arg_1044X)));
    arg3K0 = (loc_1043X + -8);
    arg3K1 = (arg_1044X + -8);
    goto L31379;}}
}
long s48_get_imported_binding(char *name_1045X)
{
  long value_1047X;
  long value_1046X;
 {  value_1046X = enter_stringAgc_n(name_1045X, (strlen((char *) name_1045X)));
  Stemp0S = value_1046X;s48_make_availableAgc(40);
  value_1047X = Stemp0S;
  Stemp0S = 1;
  return Hlookup853((Sexported_bindingsS), value_1047X, 0);}
}
long s48_define_exported_binding(char *name_1048X, long value_1049X)
{
  char * addr_1053X;
  long value_1052X;
  long binding_1051X;
  long name_1050X;
 {  Stemp0S = value_1049X;
  name_1050X = enter_stringAgc_n(name_1048X, (strlen((char *) name_1048X)));
  Stemp1S = name_1050X;s48_make_availableAgc(40);
  binding_1051X = Hlookup834((Simported_bindingsS), name_1050X, 0);
  value_1052X = Stemp0S;
  Stemp0S = 1;
  Stemp1S = 1;
  addr_1053X = (((char *) (-3 + binding_1051X))) + 16;S48_WRITE_BARRIER(binding_1051X, addr_1053X, value_1052X);
  *((long *) addr_1053X) = (long) (value_1052X);
  return binding_1051X;}
}
void s48_initialize_vm(char * stack_begin_1054X, long stack_size_1055X)
{
  char * arg3K0;
  long arg0K1;
  long arg0K0;

#ifdef USE_DIRECT_THREADING
  void *make_hash_tableAgc_return_address;
#else
  int make_hash_tableAgc_return_tag;
#endif
  long make_hash_tableAgc0_return_value;
  char * addr_1097X;
  long i_1096X;
  long table_1095X;
  long vector_1094X;
  char * addr_1093X;
  char * addr_1092X;
  long x_1091X;
  long v_1090X;
  long vector_1089X;
  char * addr_1088X;
  long blank_return_code_1087X;
  long blank_return_code_1086X;
  long blank_return_code_1085X;
  long blank_return_code_1084X;
  long blank_return_code_1083X;
  long blank_return_code_1082X;
  long blank_return_code_1081X;
  char * a_1080X;
  long size_1079X;
  char * start_1078X;
  char * stack_1077X;
  char x_1076X;
  long event_types_count_1075X;
  char * addr_1074X;
  long value_1073X;
  char * addr_1072X;
  long val_1071X;
  long index_1070X;
  long v_1069X;
  long foo_1068X;
  long table_1067X;
  long i_1066X;
  long v_1065X;
  long v_1064X;
  long exported_bindings_1063X;
  long imported_bindings_1062X;
  long n_1061X;
  long symbols_1060X;
  long maybe_1059X;
  long maybe_1058X;
  long v_1057X;
  long symbol_table_1056X;
 {  symbol_table_1056X = s48_initial_symbols();
  if ((symbol_table_1056X == 1)) {
#ifdef USE_DIRECT_THREADING
    make_hash_tableAgc_return_address = &&make_hash_tableAgc_return_0;
#else
    make_hash_tableAgc_return_tag = 0;
#endif
    goto make_hash_tableAgc;
   make_hash_tableAgc_return_0:
    v_1057X = make_hash_tableAgc0_return_value;
    Sthe_symbol_tableS = v_1057X;
    maybe_1058X = s48_find_all(1);
    if ((maybe_1058X == 1)) {s48_collect(1);
      maybe_1059X = s48_find_all(1);
      if ((maybe_1059X == 1)) {
        ps_error("insufficient heap space to build symbol table", 0);
        arg0K0 = maybe_1059X;
        goto L31523;}
      else {
        arg0K0 = maybe_1059X;
        goto L31523;}}
    else {
      arg0K0 = maybe_1058X;
      goto L31523;}}
  else {
    Sthe_symbol_tableS = symbol_table_1056X;
    goto L32275;}}
 L31523: {
  symbols_1060X = arg0K0;
  n_1061X = PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + symbols_1060X))))), 8))), 3);
  arg0K0 = 0;
  goto L31544;}
 L32275: {
  imported_bindings_1062X = s48_initial_imported_bindings();
  exported_bindings_1063X = s48_initial_exported_bindings();
  if ((1 == imported_bindings_1062X)) {
#ifdef USE_DIRECT_THREADING
    make_hash_tableAgc_return_address = &&make_hash_tableAgc_return_1;
#else
    make_hash_tableAgc_return_tag = 1;
#endif
    goto make_hash_tableAgc;
   make_hash_tableAgc_return_1:
    v_1064X = make_hash_tableAgc0_return_value;
    Simported_bindingsS = v_1064X;
#ifdef USE_DIRECT_THREADING
    make_hash_tableAgc_return_address = &&make_hash_tableAgc_return_2;
#else
    make_hash_tableAgc_return_tag = 2;
#endif
    goto make_hash_tableAgc;
   make_hash_tableAgc_return_2:
    v_1065X = make_hash_tableAgc0_return_value;
    Sexported_bindingsS = v_1065X;
    goto L32281;}
  else {
    Simported_bindingsS = imported_bindings_1062X;
    Sexported_bindingsS = exported_bindings_1063X;
    goto L32281;}}
 L31544: {
  i_1066X = arg0K0;
  if ((i_1066X == n_1061X)) {
    goto L32275;}
  else {
    table_1067X = Sthe_symbol_tableS;
    foo_1068X = *((long *) ((((char *) (-3 + symbols_1060X))) + (PS_SHIFT_LEFT_INLINE(i_1066X, 3))));
    v_1069X = Haction5350((*((long *) (((char *) (-3 + foo_1068X))))));
    index_1070X = 1023 & v_1069X;
    val_1071X = *((long *) ((((char *) (-3 + table_1067X))) + (PS_SHIFT_LEFT_INLINE(index_1070X, 3))));
    addr_1072X = (((char *) (-3 + foo_1068X))) + 8;S48_WRITE_BARRIER(foo_1068X, addr_1072X, val_1071X);
    *((long *) addr_1072X) = (long) (val_1071X);
    if ((3 == (3 & foo_1068X))) {
      arg0K0 = (-4 & foo_1068X);
      goto L30424;}
    else {
      arg0K0 = foo_1068X;
      goto L30424;}}}
 L32281: {
  Sevent_typesS = ((struct event_type**)malloc(sizeof(struct event_type*) * (Snumber_of_event_typesS)));
  if ((NULL == (Sevent_typesS))) {
    ps_error("out of memory, unable to continue", 0);
    goto L32315;}
  else {
    goto L32315;}}
 L30424: {
  value_1073X = arg0K0;
  addr_1074X = (((char *) (-3 + table_1067X))) + (PS_SHIFT_LEFT_INLINE(index_1070X, 3));S48_WRITE_BARRIER(table_1067X, addr_1074X, value_1073X);
  *((long *) addr_1074X) = (long) (value_1073X);
  arg0K0 = (1 + i_1066X);
  goto L31544;}
 L32315: {
  event_types_count_1075X = Snumber_of_event_typesS;
  Snumber_of_event_typesS = 0;
  Sunused_event_types_headS = (NULL);
  x_1076X = add_external_event_types(event_types_count_1075X);
  if (x_1076X) {
    goto L32322;}
  else {
    ps_error("out of memory, unable to continue", 0);
    goto L32322;}}
 L32322: {
  Spending_event_types_headS = (NULL);
  Spending_event_types_tailS = (NULL);
  Spending_event_types_readyS = (NULL);
  if ((stack_size_1055X < 8128)) {
    stack_1077X = (char *)malloc(65024);
    if ((stack_1077X == NULL)) {
      ps_error("out of memory, unable to continue", 0);
      arg3K0 = stack_1077X;
      arg0K1 = 8128;
      goto L25456;}
    else {
      arg3K0 = stack_1077X;
      arg0K1 = 8128;
      goto L25456;}}
  else {
    arg3K0 = stack_begin_1054X;
    arg0K1 = stack_size_1055X;
    goto L25456;}}
 L25456: {
  start_1078X = arg3K0;
  size_1079X = arg0K1;
  Sstack_beginS = start_1078X;
  Sstack_endS = (start_1078X + (PS_SHIFT_LEFT_INLINE(size_1079X, 3)));
  Sreal_stack_limitS = ((Sstack_beginS) + 1024);
  s48_Sstack_limitS = (Sreal_stack_limitS);
  SstackS = (Sstack_endS);
  ScontS = (((char *) 1));
  arg3K0 = start_1078X;
  goto L25486;}
 L25486: {
  a_1080X = arg3K0;
  if ((a_1080X == (Sstack_endS))) {s48_make_availableAgc(24);
    blank_return_code_1081X = make_blank_return_code(71, 65535, 0, 1, 0);
    *((unsigned char *) ((((char *) (-3 + blank_return_code_1081X))) + 15)) = (unsigned char) (0);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (1);
    ScontS = (SstackS);
    *((long *) (ScontS)) = (long) ((((long) ((((char *) (-3 + blank_return_code_1081X))) + 13))));
    Sbottom_of_stackS = (ScontS);
    Sheap_continuationS = 1;s48_make_availableAgc(144);
    blank_return_code_1082X = make_blank_return_code(66, 65535, 65535, 1, 0);
    *((unsigned char *) ((((char *) (-3 + blank_return_code_1082X))) + 15)) = (unsigned char) (170);
    Sinterrupted_byte_opcode_return_codeS = blank_return_code_1082X;
    blank_return_code_1083X = make_blank_return_code(66, 65535, 65535, 1, 0);
    *((unsigned char *) ((((char *) (-3 + blank_return_code_1083X))) + 15)) = (unsigned char) (171);
    Sinterrupted_native_call_return_codeS = blank_return_code_1083X;
    blank_return_code_1084X = make_blank_return_code(66, 65535, 65535, 1, 0);
    *((unsigned char *) ((((char *) (-3 + blank_return_code_1084X))) + 15)) = (unsigned char) (172);
    Snative_poll_return_codeS = blank_return_code_1084X;
    blank_return_code_1085X = make_blank_return_code(1, 65535, 65535, 1, 0);
    *((unsigned char *) ((((char *) (-3 + blank_return_code_1085X))) + 15)) = (unsigned char) (166);
    Sexception_return_codeS = blank_return_code_1085X;
    blank_return_code_1086X = make_blank_return_code(1, 65535, 65535, 1, 0);
    *((unsigned char *) ((((char *) (-3 + blank_return_code_1086X))) + 15)) = (unsigned char) (167);
    Snative_exception_return_codeS = blank_return_code_1086X;
    blank_return_code_1087X = make_blank_return_code(70, 65535, 1, 1, 0);
    *((unsigned char *) ((((char *) (-3 + blank_return_code_1087X))) + 15)) = (unsigned char) (0);
    Scall_with_values_return_codeS = blank_return_code_1087X;s48_make_availableAgc(64);s48_bignum_make_cached_constants();
    addr_1088X = s48_allocate_tracedAgc(16);
    if ((addr_1088X == NULL)) {
      arg0K0 = 1;
      goto L32360;}
    else {
      *((long *) addr_1088X) = (long) (2058);
      arg0K0 = (3 + (((long) (addr_1088X + 8))));
      goto L32360;}}
  else {
    *((long *) a_1080X) = (long) (252645135);
    arg3K0 = (a_1080X + 8);
    goto L25486;}}
 L32360: {
  vector_1089X = arg0K0;
  if ((1 == vector_1089X)) {
    ps_error("Out of space, unable to allocate", 0);
    arg0K0 = vector_1089X;
    goto L32347;}
  else {
    arg0K0 = vector_1089X;
    goto L32347;}}
 L32347: {
  v_1090X = arg0K0;
  Sempty_logS = v_1090X;
  x_1091X = Sempty_logS;
  addr_1092X = ((char *) (-3 + x_1091X));S48_WRITE_BARRIER(x_1091X, addr_1092X, 1);
  *((long *) addr_1092X) = (long) (1);
  return;}
 make_hash_tableAgc: {
{ addr_1093X = s48_allocate_tracedAgc(8200);
  if ((addr_1093X == NULL)) {
    arg0K0 = 1;
    goto L16210;}
  else {
    *((long *) addr_1093X) = (long) (2097162);
    arg0K0 = (3 + (((long) (addr_1093X + 8))));
    goto L16210;}}
 L16210: {
  vector_1094X = arg0K0;
  if ((1 == vector_1094X)) {
    ps_error("Out of space, unable to allocate", 0);
    arg0K0 = vector_1094X;
    goto L16198;}
  else {
    arg0K0 = vector_1094X;
    goto L16198;}}
 L16198: {
  table_1095X = arg0K0;
  arg0K0 = 0;
  goto L16233;}
 L16233: {
  i_1096X = arg0K0;
  if ((1024 == i_1096X)) {
    make_hash_tableAgc0_return_value = table_1095X;
#ifdef USE_DIRECT_THREADING
    goto *make_hash_tableAgc_return_address;
#else
    goto make_hash_tableAgc_return;
#endif
}
  else {
    addr_1097X = (((char *) (-3 + table_1095X))) + (PS_SHIFT_LEFT_INLINE(i_1096X, 3));S48_WRITE_BARRIER(table_1095X, addr_1097X, 1);
    *((long *) addr_1097X) = (long) (1);
    arg0K0 = (1 + i_1096X);
    goto L16233;}}
#ifndef USE_DIRECT_THREADING
 make_hash_tableAgc_return:
  switch (make_hash_tableAgc_return_tag) {
  case 0: goto make_hash_tableAgc_return_0;
  case 1: goto make_hash_tableAgc_return_1;
  default: goto make_hash_tableAgc_return_2;
  }
#endif
}

}
void s48_post_gc_cleanup(char majorP_1098X, char in_troubleP_1099X)
{

 {  (Spost_gc_cleanupS)(majorP_1098X, in_troubleP_1099X);
  return;}
}
void s48_gc_root(void)
{

 {  (Sgc_root_procS)();
  return;}
}
long s48_restart(long proc_1100X, long nargs_1101X)
{
  char *arg5K0;
  struct event_type *arg1K1;
  struct event_type *arg1K0;
  char * arg3K1;
  char * arg3K0;
  char arg4K3;
  char arg4K1;
  char arg4K0;
  char arg4K2;
  long arg0K4;
  long arg0K3;
  long arg0K2;
  long arg0K1;
  long arg0K0;
  char *merged_arg5K0;
  char * merged_arg3K0;
  FILE * merged_arg6K2;
  char merged_arg4K1;
  long merged_arg0K3;
  long merged_arg0K2;
  long merged_arg0K1;
  long merged_arg0K0;

#ifdef USE_DIRECT_THREADING
  void *maybe_write_template_return_address;
#else
  int maybe_write_template_return_tag;
#endif
  char maybe_write_template0_return_value;
#ifdef USE_DIRECT_THREADING
  void *find_template_return_address;
#else
  int find_template_return_tag;
#endif
  long find_template0_return_value;
#ifdef USE_DIRECT_THREADING
  void *loseD0_return_address;
#else
  int loseD0_return_tag;
#endif
#ifdef USE_DIRECT_THREADING
  void *unused_event_type_uid_return_address;
#else
  int unused_event_type_uid_return_tag;
#endif
  long unused_event_type_uid0_return_value;
#ifdef USE_DIRECT_THREADING
  void *ensure_stack_spaceB_return_address;
#else
  int ensure_stack_spaceB_return_tag;
#endif
  char ensure_stack_spaceB0_return_value;
#ifdef USE_DIRECT_THREADING
  void *push_list_return_address;
#else
  int push_list_return_tag;
#endif
  long push_list0_return_value;
#ifdef USE_DIRECT_THREADING
  void *pop_args_GlistSAgc_return_address;
#else
  int pop_args_GlistSAgc_return_tag;
#endif
  long pop_args_GlistSAgc0_return_value;
#ifdef USE_DIRECT_THREADING
  void *copy_listSAgc_return_address;
#else
  int copy_listSAgc_return_tag;
#endif
  long copy_listSAgc0_return_value;
#ifdef USE_DIRECT_THREADING
  void *rest_list_setupAgc_return_address;
#else
  int rest_list_setupAgc_return_tag;
#endif
#ifdef USE_DIRECT_THREADING
  void *pending_interruptP_return_address;
#else
  int pending_interruptP_return_tag;
#endif
  char pending_interruptP0_return_value;
#ifdef USE_DIRECT_THREADING
  void *proposal_d_write_return_address;
#else
  int proposal_d_write_return_tag;
#endif
#ifdef USE_DIRECT_THREADING
  void *proposal_d_read_return_address;
#else
  int proposal_d_read_return_tag;
#endif
  long proposal_d_read0_return_value;
#ifdef USE_DIRECT_THREADING
  void *pop_continuationB_return_address;
#else
  int pop_continuationB_return_tag;
#endif
#ifdef USE_DIRECT_THREADING
  void *shift_space_return_address;
#else
  int shift_space_return_tag;
#endif
  long shift_space0_return_value;
#ifdef USE_DIRECT_THREADING
  void *get_current_port_return_address;
#else
  int get_current_port_return_tag;
#endif
  long get_current_port0_return_value;
#ifdef USE_DIRECT_THREADING
  void *okay_argument_list_return_address;
#else
  int okay_argument_list_return_tag;
#endif
  char okay_argument_list0_return_value;
  long okay_argument_list1_return_value;
#ifdef USE_DIRECT_THREADING
  void *copy_continuation_from_heapB_return_address;
#else
  int copy_continuation_from_heapB_return_tag;
#endif
  char * copy_continuation_from_heapB0_return_value;
#ifdef USE_DIRECT_THREADING
  void *s48_pop_interrupt_state_return_address;
#else
  int s48_pop_interrupt_state_return_tag;
#endif
#ifdef USE_DIRECT_THREADING
  void *move_args_above_contB_return_address;
#else
  int move_args_above_contB_return_tag;
#endif
#ifdef USE_DIRECT_THREADING
  void *use_event_type_uidB_return_address;
#else
  int use_event_type_uidB_return_tag;
#endif
  long template_1102X;
  char not_firstP_1103X;
  FILE * out_1104X;
  char * start_1105X;
  long count_1106X;
  long code_vector_1107X;
  char *message_1108X;
  long need_1109X;
  long list_1110X;
  long count_1111X;
  long start_1112X;
  long count_1113X;
  long list_1114X;
  long length_1115X;
  long wants_stack_args_1116X;
  long stack_arg_count_1117X;
  long list_args_1118X;
  long list_arg_count_1119X;
  long stob_1120X;
  long index_1121X;
  long value_1122X;
  long stob_1123X;
  long index_1124X;
  long x_1125X;
  long n_1126X;
  long marker_1127X;
  long list_1128X;
  long cont_1129X;
  long stack_arg_count_1130X;
  long nargs_1131X;
  long id_1132X;
  long obj_2789X;
  long obj_2788X;
  long name_2787X;
  long next_2786X;
  long i_2785X;
  long v_2784X;
  long why_2783X;
  long size_2782X;
  char * pointer_2781X;
  char v_2780X;
  long v_2779X;
  long v_2778X;
  char v_2777X;
  long v_2776X;
  char not_firstP_2775X;
  long cont_2774X;
  long size_2773X;
  char * pointer_2772X;
  long v_2771X;
  char * pointer_2770X;
  char * code_pointer_2769X;
  long cont_2768X;
  char not_firstP_2767X;
  char * cont_2766X;
  char not_firstP_2765X;
  long template_2764X;
  FILE * out_2763X;
  long current_code_2762X;
  char v_2761X;
  char interruptP_2760X;
  long x_2759X;
  long l_2758X;
  long i_2757X;
  long list_2756X;
  char v_2755X;
  long x_2754X;
  char * addr_2753X;
  long a_2752X;
  long count_2751X;
  long args_2750X;
  long value_2749X;
  char * addr_2748X;
  long x_2747X;
  char * addr_2746X;
  long a_2745X;
  long last_2744X;
  long l_2743X;
  long x_2742X;
  char * addr_2741X;
  long a_2740X;
  long value_2739X;
  long x_2738X;
  long v_2737X;
  long x_2736X;
  long v_2735X;
  long count_2734X;
  long x_2733X;
  long interrupt_bit_2732X;
  long status_2731X;
  long channel_2730X;
  long type_2729X;
  char * addr_2728X;
  long next_stob_2727X;
  long i_2726X;
  long log_2725X;
  long v_2724X;
  long next_stob_2723X;
  long i_2722X;
  long log_2721X;
  long v_2720X;
  long v_2719X;
  long size_2718X;
  char * pointer_2717X;
  char * cont_2716X;
  long v_2715X;
  long v_2714X;
  long n_2713X;
  long extra_2712X;
  long x_size_2711X;
  char *v_2710X;
  long v_2709X;
  long obj_2708X;
  long env_2707X;
  long thread_2706X;
  char move_slowP_2705X;
  long slow_2704X;
  long len_2703X;
  long fast_2702X;
  char * new_stack_2701X;
  char * new_cont_2700X;
  long stack_size_2699X;
  char * addr_2698X;
  long x_2697X;
  long proposal_2696X;
  long p_2695X;
  char * arg_2694X;
  char * loc_2693X;
  char * top_of_args_2692X;
  struct event_type *unused_type_2691X;
  struct event_type *previous_2690X;
  char v_2689X;
  struct event_type *type_2688X;
  long v_2687X;
  long v_2686X;
  long stob_2685X;
  long v_2684X;
  long stob_2683X;
  char * addr_2682X;
  long x_2681X;
  char * addr_2680X;
  char * addr_2679X;
  long value_2678X;
  char * addr_2677X;
  long value_2676X;
  long copies_2675X;
  long link_2674X;
  long verify_2673X;
  long value_2672X;
  long copies_2671X;
  long stob_2670X;
  long i_2669X;
  long val_2668X;
  long val_2667X;
  long v_2666X;
  char * v_2665X;
  char * addr_2664X;
  long val_2663X;
  char * addr_2662X;
  char * addr_2661X;
  long val_2660X;
  char * addr_2659X;
  long value_2658X;
  long len_2657X;
  long s2_2656X;
  long foo_2655X;
  long previous_foo_2654X;
  char * addr_2653X;
  long verify_2652X;
  long value_2651X;
  long log_2650X;
  long stob_2649X;
  long i_2648X;
  long x_2647X;
  long status_2646X;
  long v_2645X;
  char * addr_2644X;
  long value_2643X;
  long val_2642X;
  long val_2641X;
  long n_2640X;
  char v_2639X;
  char * external_bignum_2638X;
  long val_2637X;
  long v_2636X;
  char * v_2635X;
  long val_2634X;
  long v_2633X;
  char * v_2632X;
  long x_2631X;
  long val_2630X;
  long v_2629X;
  char * v_2628X;
  char * addr_2627X;
  long value_2626X;
  long offset_2625X;
  long i_2624X;
  long count_2623X;
  char * addr_2622X;
  long value_2621X;
  long offset_2620X;
  long i_2619X;
  long count_2618X;
  long n_2617X;
  char * addr_2616X;
  long val_2615X;
  long count_2614X;
  char out_of_spaceP_2613X;
  char encoding_okP_2612X;
  char * addr_2611X;
  long val_2610X;
  long count_2609X;
  char out_of_spaceP_2608X;
  char encoding_okP_2607X;
  char codec_okP_2606X;
  long count_2605X;
  long value_2604X;
  char incompleteP_2603X;
  char okP_2602X;
  char encoding_okP_2601X;
  char * addr_2600X;
  long val_2599X;
  char * addr_2598X;
  char * addr_2597X;
  long val_2596X;
  char * addr_2595X;
  char * addr_2594X;
  long val_2593X;
  long count_2592X;
  long value_2591X;
  char incompleteP_2590X;
  char okP_2589X;
  char encoding_okP_2588X;
  long x_2587X;
  long x_2586X;
  long shifted_2585X;
  long j_2584X;
  long bits_2583X;
  long bucket_2582X;
  char * addr_2581X;
  char * addr_2580X;
  long value_2579X;
  char * addr_2578X;
  char * addr_2577X;
  char * addr_2576X;
  long value_2575X;
  char * addr_2574X;
  char * addr_2573X;
  long value_2572X;
  long proposal_2571X;
  long entry_2570X;
  long thing_2569X;
  long log_2568X;
  long copies_2567X;
  char * addr_2566X;
  long x_2565X;
  long val_2564X;
  long v_2563X;
  long reason_2562X;
  long channel_2561X;
  long channel_2560X;
  long link_2559X;
  long val_2558X;
  long x_2557X;
  char * addr_2556X;
  long b_2555X;
  long shifted_2554X;
  long j_2553X;
  long bits_2552X;
  long val_2551X;
  long v_2550X;
  long n_2549X;
  char v_2548X;
  char * external_bignum_2547X;
  char * x_2546X;
  char * v_2545X;
  long v_2544X;
  char * x_2543X;
  long val_2542X;
  long v_2541X;
  char * v_2540X;
  long n_2539X;
  long val_2538X;
  long val_2537X;
  long val_2536X;
  long val_2535X;
  long val_2534X;
  long val_2533X;
  long val_2532X;
  long v_2531X;
  char * v_2530X;
  long x_2529X;
  long val_2528X;
  long v_2527X;
  char * v_2526X;
  long val_2525X;
  long val_2524X;
  long val_2523X;
  long val_2522X;
  char * arg_2521X;
  char * loc_2520X;
  long x_2519X;
  long l_2518X;
  long stack_nargs_2517X;
  long x_2516X;
  long v_2515X;
  long x_2514X;
  long v_2513X;
  long v_2512X;
  long v_2511X;
  long bytes_used_2510X;
  long count_2509X;
  long index_2508X;
  long env_2507X;
  long offset_2506X;
  long i_2505X;
  long bytes_used_2504X;
  long count_2503X;
  long env_2502X;
  long offset_2501X;
  long i_2500X;
  long v_2499X;
  long n_2498X;
  long x_2497X;
  long x_2496X;
  long x_2495X;
  long obj_2494X;
  long i_2493X;
  long count_2492X;
  char out_of_spaceP_2491X;
  char encoding_okP_2490X;
  long count_2489X;
  char out_of_spaceP_2488X;
  char encoding_okP_2487X;
  long count_2486X;
  char out_of_spaceP_2485X;
  char encoding_okP_2484X;
  long count_2483X;
  char * buffer_2482X;
  long encoding_2481X;
  long i_2480X;
  long count_2479X;
  char out_of_spaceP_2478X;
  char encoding_okP_2477X;
  char codec_okP_2476X;
  long count_2475X;
  char out_of_spaceP_2474X;
  char encoding_okP_2473X;
  long count_2472X;
  char out_of_spaceP_2471X;
  char encoding_okP_2470X;
  long count_2469X;
  char out_of_spaceP_2468X;
  char encoding_okP_2467X;
  long count_2466X;
  char * buffer_2465X;
  long value_2464X;
  long encoding_2463X;
  long code_point_2462X;
  long code_point_2461X;
  long count_2460X;
  long value_2459X;
  char incompleteP_2458X;
  char okP_2457X;
  long count_2456X;
  long value_2455X;
  char incompleteP_2454X;
  char okP_2453X;
  long count_2452X;
  long value_2451X;
  char incompleteP_2450X;
  char okP_2449X;
  long count_2448X;
  char * buffer_2447X;
  long encoding_2446X;
  long l_2445X;
  long codec_2444X;
  long p_2443X;
  long i_2442X;
  char * addr_2441X;
  long val_2440X;
  long code_point_2439X;
  long code_point_2438X;
  long count_2437X;
  long value_2436X;
  char incompleteP_2435X;
  char okP_2434X;
  long count_2433X;
  long value_2432X;
  char incompleteP_2431X;
  char okP_2430X;
  long count_2429X;
  long value_2428X;
  char incompleteP_2427X;
  char okP_2426X;
  long count_2425X;
  char * buffer_2424X;
  long encoding_2423X;
  char * addr_2422X;
  long val_2421X;
  long l_2420X;
  long codec_2419X;
  long p_2418X;
  long i_2417X;
  long x_2416X;
  long x_2415X;
  char * addr_2414X;
  long value_2413X;
  long d_2412X;
  long i_2411X;
  long l_2410X;
  long x_2409X;
  long link_2408X;
  long index_2407X;
  long v_2406X;
  long table_2405X;
  long val_2404X;
  char x_2403X;
  char minutesP_2402X;
  long vector_2401X;
  char * addr_2400X;
  long x_2399X;
  long verify_2398X;
  long value_2397X;
  long copies_2396X;
  long stob_2395X;
  long i_2394X;
  char * addr_2393X;
  long v_2392X;
  char * addr_2391X;
  char * addr_2390X;
  long val_2389X;
  long x_2388X;
  char * addr_2387X;
  char * addr_2386X;
  char * addr_2385X;
  long status_2384X;
  char pendingP_2383X;
  char eofP_2382X;
  long got_2381X;
  char v_2380X;
  long count_2379X;
  long start_2378X;
  char waitP_2377X;
  long status_2376X;
  long channel_2375X;
  long v_2374X;
  long v_2373X;
  char x_2372X;
  char temp_2371X;
  long index_2370X;
  long len_2369X;
  long s2_2368X;
  long foo_2367X;
  long i_2366X;
  long i_2365X;
  long i_2364X;
  char * addr_2363X;
  long i_2362X;
  long rest_list_2361X;
  long i_2360X;
  long v_2359X;
  long n_2358X;
  char v_2357X;
  char * external_bignum_2356X;
  char * x_2355X;
  long val_2354X;
  long v_2353X;
  char * v_2352X;
  char * v_2351X;
  long value_2350X;
  long needed_2349X;
  long y_2348X;
  long y_2347X;
  long x_2346X;
  long val_2345X;
  long v_2344X;
  char * v_2343X;
  long val_2342X;
  long v_2341X;
  char * v_2340X;
  long val_2339X;
  long val_2338X;
  long val_2337X;
  long count_2336X;
  long x_2335X;
  char * v_2334X;
  long value_2333X;
  long extra_2332X;
  long length_2331X;
  long x_2330X;
  long val_2329X;
  long c_2328X;
  long b_2327X;
  long val_2326X;
  long c_2325X;
  long b_2324X;
  long val_2323X;
  char b_2322X;
  long val_2321X;
  char b_2320X;
  long val_2319X;
  long v_2318X;
  long v_2317X;
  long v_2316X;
  long val_2315X;
  long v_2314X;
  long v_2313X;
  long v_2312X;
  long val_2311X;
  char b_2310X;
  long y_2309X;
  long x_2308X;
  long rem_2307X;
  long quot_2306X;
  char div_by_zeroP_2305X;
  char x_2304X;
  long c_2303X;
  long b_2302X;
  long val_2301X;
  long val_2300X;
  long val_2299X;
  long c_2298X;
  long mid_c_2297X;
  long v_2296X;
  long v_2295X;
  long lo_c_2294X;
  long hi_b_2293X;
  long hi_a_2292X;
  long lo_b_2291X;
  long lo_a_2290X;
  long b_2289X;
  long val_2288X;
  double x_2287X;
  long args_2286X;
  char * arg_top_2285X;
  long list_arg_count_2284X;
  long list_args_2283X;
  long stack_nargs_2282X;
  long bytes_used_2281X;
  long count_2280X;
  long v_2279X;
  char * arg_2278X;
  char * loc_2277X;
  long v_2276X;
  long v_2275X;
  long v_2274X;
  long bytes_used_2273X;
  long args_2272X;
  long list_args_2271X;
  long stack_nargs_2270X;
  long v_2269X;
  long x_2268X;
  long v_2267X;
  long cont_2266X;
  long size_2265X;
  char * pointer_2264X;
  char * cont_2263X;
  long protocol_skip_2262X;
  long template_2261X;
  long v_2260X;
  char v_2259X;
  char * arg_2258X;
  char * loc_2257X;
  char * addr_2256X;
  long value_2255X;
  long offset_2254X;
  long i_2253X;
  long count_2252X;
  char * addr_2251X;
  long value_2250X;
  long offset_2249X;
  long i_2248X;
  long count_2247X;
  long n_2246X;
  long sig_2245X;
  char x_2244X;
  long channel_2243X;
  long n_2242X;
  long x_2241X;
  long arg_count_2240X;
  long stuff_2239X;
  long vector_2238X;
  long count_2237X;
  char out_of_spaceP_2236X;
  char encoding_okP_2235X;
  long count_2234X;
  char out_of_spaceP_2233X;
  char encoding_okP_2232X;
  long count_2231X;
  char out_of_spaceP_2230X;
  char encoding_okP_2229X;
  long count_2228X;
  char * buffer_2227X;
  long encoding_2226X;
  long x_2225X;
  long l_2224X;
  long i_2223X;
  long b_2222X;
  long codec_2221X;
  long port_2220X;
  long Kchar_2219X;
  long b_2218X;
  long port_2217X;
  long b_2216X;
  long port_2215X;
  char * addr_2214X;
  long val_2213X;
  long i_2212X;
  long b_2211X;
  long p_2210X;
  long port_2209X;
  long byte_2208X;
  long i_2207X;
  long p_2206X;
  long p_2205X;
  long b_2204X;
  long port_2203X;
  char * addr_2202X;
  long val_2201X;
  long i_2200X;
  long p_2199X;
  long p_2198X;
  long b_2197X;
  long port_2196X;
  long x_2195X;
  long x_2194X;
  long count_2193X;
  long value_2192X;
  char incompleteP_2191X;
  char okP_2190X;
  char encoding_okP_2189X;
  long x_2188X;
  long x_2187X;
  long count_2186X;
  char out_of_spaceP_2185X;
  char okP_2184X;
  char encoding_okP_2183X;
  long v_2182X;
  long len_2181X;
  long v_2180X;
  long v_2179X;
  long len_2178X;
  long val_2177X;
  long x_2176X;
  long list_2175X;
  long head_2174X;
  char move_slowP_2173X;
  long slow_2172X;
  long list_2171X;
  long obj_2170X;
  char * addr_2169X;
  long len_2168X;
  long x_2167X;
  long val_2166X;
  long mseconds_2165X;
  long seconds_2164X;
  long option_2163X;
  struct event_type *type_2162X;
  struct event_type *type_2161X;
  long uid_2160X;
  long x_2159X;
  long vector_2158X;
  char firstP_2157X;
  long x_2156X;
  long x_2155X;
  long v_2154X;
  long v_2153X;
  long x_2152X;
  long result_2151X;
  char * args_2150X;
  long proc_2149X;
  long name_2148X;
  long rest_list_2147X;
  long x_2146X;
  long result_2145X;
  char * args_2144X;
  long proc_2143X;
  long name_2142X;
  long rest_list_2141X;
  long x_2140X;
  long x_2139X;
  long x_2138X;
  long x_2137X;
  long value_2136X;
  long vector_2135X;
  long type_2134X;
  char firstP_2133X;
  long vector_2132X;
  char firstP_2131X;
  long x_2130X;
  long x_2129X;
  long status_2128X;
  long x_2127X;
  char * addr_2126X;
  long next_stob_2125X;
  long i_2124X;
  long x_2123X;
  long v_2122X;
  long next_stob_2121X;
  long i_2120X;
  long value_2119X;
  long x_2118X;
  char * addr_2117X;
  long count_2116X;
  long to_index_2115X;
  long from_index_2114X;
  long copies_2113X;
  long left_2112X;
  long value_2111X;
  long verify_2110X;
  long value_2109X;
  long log_2108X;
  long stob_2107X;
  long i_2106X;
  char * addr_2105X;
  long old_2104X;
  long x_2103X;
  char * addr_2102X;
  long channel_2101X;
  long res_2100X;
  long i_2099X;
  long x_2098X;
  long y_2097X;
  long n_2096X;
  char * addr_2095X;
  long prev_2094X;
  long ch_2093X;
  long x_2092X;
  long val_2091X;
  long x_2090X;
  long val_2089X;
  long val_2088X;
  long x_2087X;
  long val_2086X;
  long x_2085X;
  long x_2084X;
  long v_2083X;
  long v_2082X;
  char *filename_2081X;
  long val_2080X;
  long x_2079X;
  char * addr_2078X;
  char * addr_2077X;
  long x_2076X;
  long val_2075X;
  long x_2074X;
  long bucket_2073X;
  long x_2072X;
  long x_2071X;
  long shifted_2070X;
  long j_2069X;
  long bits_2068X;
  long x_2067X;
  long x_2066X;
  long scalar_value_2065X;
  long j_2064X;
  long bits_2063X;
  long x_2062X;
  long x_2061X;
  long vector_2060X;
  long vector_2059X;
  long x_2058X;
  long x_2057X;
  long x_2056X;
  long vector_2055X;
  long new_2054X;
  char * addr_2053X;
  long value_2052X;
  long value_2051X;
  long x_2050X;
  char * addr_2049X;
  long value_2048X;
  long i_2047X;
  long value_2046X;
  long i_2045X;
  long value_2044X;
  long val_2043X;
  long val_2042X;
  long x_2041X;
  long val_2040X;
  long x_2039X;
  long val_2038X;
  long val_2037X;
  char * v_2036X;
  long value_2035X;
  long needed_2034X;
  long y_2033X;
  long x_2032X;
  long result_2031X;
  long x_2030X;
  long x_2029X;
  long x_2028X;
  long count_2027X;
  long value_2026X;
  long val_2025X;
  long val_2024X;
  long val_2023X;
  long x_2022X;
  long val_2021X;
  long x_2020X;
  long n_2019X;
  long x_2018X;
  long x_2017X;
  long v_2016X;
  long x_2015X;
  long n_2014X;
  long a_2013X;
  long a_2012X;
  long val_2011X;
  long val_2010X;
  char b_2009X;
  long val_2008X;
  char b_2007X;
  long val_2006X;
  char b_2005X;
  long val_2004X;
  long Kdouble_2003X;
  char * addr_2002X;
  double value_2001X;
  long value_2000X;
  double x_1999X;
  long value_1998X;
  long a_1997X;
  long Kdouble_1996X;
  char * addr_1995X;
  double y_1994X;
  long value_1993X;
  double x_1992X;
  long value_1991X;
  long val_1990X;
  long v_1989X;
  char * v_1988X;
  long Kdouble_1987X;
  char * addr_1986X;
  double y_1985X;
  long value_1984X;
  double x_1983X;
  long value_1982X;
  long a_1981X;
  long Kdouble_1980X;
  char * addr_1979X;
  double y_1978X;
  long value_1977X;
  double x_1976X;
  long value_1975X;
  long val_1974X;
  long v_1973X;
  char * v_1972X;
  long n_1971X;
  long val_1970X;
  long val_1969X;
  long delta_1968X;
  long delta_1967X;
  long offset_1966X;
  long index_1965X;
  long v_1964X;
  char * arg_top_1963X;
  long args_1962X;
  long count_1961X;
  long size_1960X;
  char * pointer_1959X;
  char * cont_1958X;
  long offset_1957X;
  long cont_1956X;
  long args_1955X;
  long args_1954X;
  long v_1953X;
  long v_1952X;
  long protocol_1951X;
  char * code_pointer_1950X;
  long list_arg_count_1949X;
  long list_args_1948X;
  long stack_nargs_1947X;
  long args_1946X;
  long x_1945X;
  long args_1944X;
  long x_1943X;
  long x_1942X;
  long x_1941X;
  char * addr_1940X;
  long a_1939X;
  long wants_stack_args_1938X;
  long size_1937X;
  char * pointer_1936X;
  char * cont_1935X;
  long proc_1934X;
  long offset_1933X;
  long cont_1932X;
  long protocol_1931X;
  char * code_pointer_1930X;
  long obj_1929X;
  char * addr_1928X;
  long list_args_1927X;
  long follower_1926X;
  long list_1925X;
  long x_1924X;
  long args_1923X;
  long list_arg_count_1922X;
  char okayP_1921X;
  long stack_nargs_1920X;
  long list_args_1919X;
  long obj_1918X;
  long obj_1917X;
  long list_arg_count_1916X;
  long list_args_1915X;
  long stack_arg_count_1914X;
  char * code_pointer_1913X;
  long return_pointer_offset_1912X;
  long stack_arg_count_1911X;
  long skip_1910X;
  long template_1909X;
  char * code_pointer_1908X;
  long stack_arg_count_1907X;
  long skip_1906X;
  long template_1905X;
  long skip_1904X;
  long obj_1903X;
  char interruptP_1902X;
  long protocol_1901X;
  long code_1900X;
  long template_1899X;
  long obj_1898X;
  long stack_arg_count_1897X;
  long cont_1896X;
  long index_1895X;
  long value_1894X;
  long index_1893X;
  long value_1892X;
  long move_1891X;
  long index_1890X;
  long value_1889X;
  long move_1888X;
  long n_1887X;
  long value_1886X;
  long i_1885X;
  char * addr_1884X;
  long x_1883X;
  char * addr_1882X;
  long a_1881X;
  long offset_1880X;
  long i_1879X;
  long count_1878X;
  long total_count_1877X;
  long offset_1876X;
  long i_1875X;
  long new_env_1874X;
  char * addr_1873X;
  long x_1872X;
  char * addr_1871X;
  long a_1870X;
  long offset_1869X;
  long i_1868X;
  long count_1867X;
  long total_count_1866X;
  long offset_1865X;
  long i_1864X;
  long new_env_1863X;
  long v_1862X;
  long x_1861X;
  long x_1860X;
  long args_1859X;
  long length_1858X;
  char okayP_1857X;
  long list_args_1856X;
  long stack_nargs_1855X;
  long maybe_cont_1854X;
  long v_1853X;
  long v_1852X;
  long v_1851X;
  long code_1850X;
  long n_1849X;
  char * addr_1848X;
  long x_1847X;
  long x_1846X;
  long x_1845X;
  char v_1844X;
  long return_address_1843X;
  long template_1842X;
  long obj_1841X;
  long stack_arg_count_1840X;
  long tag_1839X;
  long n_1838X;
  char still_readyP_1837X;
  long uid_1836X;
  char v_1835X;
  char * addr_1834X;
  long next_1833X;
  long channel_1832X;
  long n_1831X;
  long x_1830X;
  long handlers_1829X;
  long m_1828X;
  long i_1827X;
  FILE * out_1826X;
  long x_1825X;
  long x_1824X;
  char * addr_1823X;
  long len_1822X;
  char *raw_1821X;
  long v_1820X;
  long v_1819X;
  long v_1818X;
  long v_1817X;
  long v_1816X;
  long v_1815X;
  long v_1814X;
  long v_1813X;
  long v_1812X;
  long v_1811X;
  long v_1810X;
  long v_1809X;
  long v_1808X;
  long v_1807X;
  long code_point_1806X;
  long code_point_1805X;
  long count_1804X;
  long value_1803X;
  char incompleteP_1802X;
  long count_1801X;
  long value_1800X;
  char incompleteP_1799X;
  long count_1798X;
  long value_1797X;
  char incompleteP_1796X;
  char * buffer_1795X;
  long count_1794X;
  long start_1793X;
  long encoding_1792X;
  long arg4_1791X;
  long arg3_1790X;
  long arg2_1789X;
  long code_point_1788X;
  long code_point_1787X;
  long count_1786X;
  long value_1785X;
  char incompleteP_1784X;
  char okP_1783X;
  long count_1782X;
  long value_1781X;
  char incompleteP_1780X;
  char okP_1779X;
  long count_1778X;
  long value_1777X;
  char incompleteP_1776X;
  char okP_1775X;
  char * buffer_1774X;
  long count_1773X;
  long start_1772X;
  long encoding_1771X;
  long arg4_1770X;
  long arg3_1769X;
  long arg2_1768X;
  long count_1767X;
  char out_of_spaceP_1766X;
  long count_1765X;
  char out_of_spaceP_1764X;
  long count_1763X;
  char out_of_spaceP_1762X;
  char * buffer_1761X;
  long count_1760X;
  long start_1759X;
  long value_1758X;
  long encoding_1757X;
  long arg5_1756X;
  long arg4_1755X;
  long arg3_1754X;
  long arg2_1753X;
  long count_1752X;
  char out_of_spaceP_1751X;
  char encoding_okP_1750X;
  long count_1749X;
  char out_of_spaceP_1748X;
  char encoding_okP_1747X;
  long count_1746X;
  char out_of_spaceP_1745X;
  char encoding_okP_1744X;
  char * buffer_1743X;
  long count_1742X;
  long start_1741X;
  long value_1740X;
  long encoding_1739X;
  long arg5_1738X;
  long arg4_1737X;
  long arg3_1736X;
  long arg2_1735X;
  long x_1734X;
  long ec2_1733X;
  long rt1_1732X;
  long value_1731X;
  long index_1730X;
  long arg4_1729X;
  long arg3_1728X;
  long arg2_1727X;
  long x_1726X;
  long ec2_1725X;
  long rt1_1724X;
  long index_1723X;
  long arg3_1722X;
  long arg2_1721X;
  long ec2_1720X;
  long x_1719X;
  char x_1718X;
  char x_1717X;
  long arg2_1716X;
  long list_1715X;
  long arg2_1714X;
  long x_1713X;
  long n_1712X;
  long arg2_1711X;
  long len_1710X;
  long x_1709X;
  long obj_1708X;
  long arg2_1707X;
  long x_1706X;
  long arg2_1705X;
  long x_1704X;
  long status_1703X;
  long value_1702X;
  long key_1701X;
  long arg2_1700X;
  long x_1699X;
  long val_1698X;
  char *string_1697X;
  long val_1696X;
  long key_1695X;
  long x_1694X;
  long mseconds_1693X;
  long seconds_1692X;
  long mseconds_1691X;
  long seconds_1690X;
  long mseconds_1689X;
  long seconds_1688X;
  long x_1687X;
  long other_1686X;
  long option_1685X;
  long arg2_1684X;
  long x_1683X;
  long index_1682X;
  char * addr_1681X;
  long val_1680X;
  long uid_1679X;
  char * addr_1678X;
  long val_1677X;
  char v_1676X;
  char * addr_1675X;
  long val_1674X;
  long uid_1673X;
  long uid_val_1672X;
  long arg_1671X;
  long x_1670X;
  long arg2_1669X;
  long x_1668X;
  long arg2_1667X;
  long x_1666X;
  long rest_list_1665X;
  long p_1664X;
  long nargs_1663X;
  long p_1662X;
  long x_1661X;
  long rest_list_1660X;
  long p_1659X;
  long nargs_1658X;
  long p_1657X;
  long x_1656X;
  long arg2_1655X;
  long x_1654X;
  long p_1653X;
  long v_1652X;
  long v_1651X;
  long template_1650X;
  long return_address_1649X;
  long v_1648X;
  long p_1647X;
  long v_1646X;
  long v_1645X;
  long code_1644X;
  long pc_1643X;
  long p_1642X;
  long old_1641X;
  long temp_1640X;
  long obj_1639X;
  long opcode_1638X;
  long bc_pc_1637X;
  long bc_code_1636X;
  long exception_1635X;
  long data_1634X;
  long opcode_1633X;
  long pc_1632X;
  long size_1631X;
  long exception_1630X;
  long code_1629X;
  long data_1628X;
  long temp_1627X;
  long obj_1626X;
  long val_1625X;
  long x_1624X;
  long x_1623X;
  long type_1622X;
  long x_1621X;
  long x_1620X;
  long x_1619X;
  long bytes_1618X;
  long x_1617X;
  long other_1616X;
  long key_1615X;
  long arg2_1614X;
  long x_1613X;
  char * addr_1612X;
  long b_1611X;
  long x_1610X;
  char * addr_1609X;
  long proc_1608X;
  long arg2_1607X;
  long x_1606X;
  long obj_1605X;
  long close_status_1604X;
  long close_status_1603X;
  long status_1602X;
  long status_1601X;
  long status_1600X;
  long status_1599X;
  FILE * port_1598X;
  long undumpables_1597X;
  long obj_1596X;
  long arg4_1595X;
  long arg3_1594X;
  long arg2_1593X;
  long x_1592X;
  long log_1591X;
  long index_1590X;
  long x_1589X;
  long len_1588X;
  long byte_1587X;
  long index_1586X;
  long arg3_1585X;
  long arg2_1584X;
  long log_1583X;
  long index_1582X;
  long x_1581X;
  long len_1580X;
  long index_1579X;
  long arg2_1578X;
  long v_1577X;
  long count_1576X;
  long to_index_1575X;
  long from_index_1574X;
  long arg5_1573X;
  long arg4_1572X;
  long arg3_1571X;
  long arg2_1570X;
  long v_1569X;
  long x_1568X;
  long offset_1567X;
  long type_1566X;
  long stob_1565X;
  long log_1564X;
  long proposal_1563X;
  long proposal_1562X;
  long weak_pointer_1561X;
  char * addr_1560X;
  char * addr_1559X;
  long next_1558X;
  long channel_1557X;
  long n_1556X;
  char * addr_1555X;
  long head_1554X;
  long channel_1553X;
  long obj_1552X;
  long status_1551X;
  char readyP_1550X;
  long channel_1549X;
  long obj_1548X;
  long x_1547X;
  char x_1546X;
  long x_1545X;
  long param_1544X;
  long x_1543X;
  char * addr_1542X;
  char * addr_1541X;
  long status_1540X;
  char pendingP_1539X;
  long got_1538X;
  char v_1537X;
  long count_1536X;
  long start_1535X;
  long arg4_1534X;
  long arg3_1533X;
  long arg2_1532X;
  long x_1531X;
  long arg5_1530X;
  long arg4_1529X;
  long arg3_1528X;
  long arg2_1527X;
  long status_1526X;
  long channel_1525X;
  long obj_1524X;
  long x_1523X;
  long close_silentlyP_1522X;
  long mode_1521X;
  long arg4_1520X;
  long arg3_1519X;
  long arg2_1518X;
  long x_1517X;
  long x_1516X;
  long x_1515X;
  long arg2_1514X;
  long descriptor_1513X;
  long x_1512X;
  long obj_1511X;
  long link_1510X;
  long index_1509X;
  long v_1508X;
  long string_1507X;
  long table_1506X;
  long obj_1505X;
  long y_1504X;
  long y_1503X;
  long count_1502X;
  long to_index_1501X;
  long from_index_1500X;
  long arg5_1499X;
  long arg4_1498X;
  long arg3_1497X;
  long arg2_1496X;
  long len_1495X;
  long Kchar_1494X;
  long index_1493X;
  long arg3_1492X;
  long arg2_1491X;
  long len_1490X;
  long index_1489X;
  long arg2_1488X;
  long x_1487X;
  long obj_1486X;
  char * addr_1485X;
  long len_1484X;
  long init_1483X;
  long len_1482X;
  long arg2_1481X;
  long x_1480X;
  char * addr_1479X;
  char x_1478X;
  long init_1477X;
  long len_1476X;
  long arg2_1475X;
  long len_1474X;
  long Kchar_1473X;
  long index_1472X;
  long arg3_1471X;
  long arg2_1470X;
  long len_1469X;
  long index_1468X;
  long arg2_1467X;
  long obj_1466X;
  long x_1465X;
  char * addr_1464X;
  long init_1463X;
  long len_1462X;
  long arg2_1461X;
  char * addr_1460X;
  long v_1459X;
  long index_1458X;
  long len_1457X;
  long type_1456X;
  long value_1455X;
  long arg3_1454X;
  long arg2_1453X;
  long v_1452X;
  long v_1451X;
  long index_1450X;
  long len_1449X;
  long type_1448X;
  long index_1447X;
  long arg2_1446X;
  char * addr_1445X;
  long len_in_bytes_1444X;
  long len_1443X;
  long type_1442X;
  long init_1441X;
  long arg2_1440X;
  long v_1439X;
  long offset_1438X;
  long type_1437X;
  long value_1436X;
  long arg2_1435X;
  long offset_1434X;
  long type_1433X;
  long stob_1432X;
  long rest_list_1431X;
  long stack_nargs_1430X;
  long p_1429X;
  long new_1428X;
  char * addr_1427X;
  long len_1426X;
  long type_1425X;
  long len_1424X;
  long p_1423X;
  long new_1422X;
  char * addr_1421X;
  long len_1420X;
  long type_1419X;
  long len_1418X;
  long type_1417X;
  long stob_1416X;
  long type_1415X;
  long x_1414X;
  long x_1413X;
  long x_1412X;
  long x_1411X;
  long x_1410X;
  long x_1409X;
  long x_1408X;
  long x_1407X;
  long arg2_1406X;
  long x_1405X;
  long arg2_1404X;
  long x_1403X;
  long v_1402X;
  long v_1401X;
  long y_1400X;
  long arg2_1399X;
  long y_1398X;
  long arg2_1397X;
  long y_1396X;
  long arg2_1395X;
  long y_1394X;
  long arg2_1393X;
  long x_1392X;
  long x_1391X;
  long x_1390X;
  long x_1389X;
  long arg2_1388X;
  long x_1387X;
  long arg2_1386X;
  long x_1385X;
  long arg2_1384X;
  long x_1383X;
  long x_1382X;
  long x_1381X;
  long x_1380X;
  long x_1379X;
  long x_1378X;
  long x_1377X;
  long x_1376X;
  long x_1375X;
  long x_1374X;
  long x_1373X;
  long n_1372X;
  long n_1371X;
  long n_1370X;
  long n_1369X;
  long n_1368X;
  long a_1367X;
  long val_1366X;
  long y_1365X;
  long arg2_1364X;
  long b_1363X;
  long a_1362X;
  long val_1361X;
  long y_1360X;
  long arg2_1359X;
  long y_1358X;
  long arg2_1357X;
  long y_1356X;
  long arg2_1355X;
  long y_1354X;
  long arg2_1353X;
  long y_1352X;
  long arg2_1351X;
  long y_1350X;
  long arg2_1349X;
  long b_1348X;
  long a_1347X;
  long y_1346X;
  long arg2_1345X;
  long x_1344X;
  long y_1343X;
  long arg2_1342X;
  long b_1341X;
  long a_1340X;
  long y_1339X;
  long arg2_1338X;
  long x_1337X;
  long y_1336X;
  long arg2_1335X;
  long x_1334X;
  long x_1333X;
  long n_1332X;
  long n_1331X;
  long n_1330X;
  long x_1329X;
  long x_1328X;
  long arg2_1327X;
  long rest_list_1326X;
  long x_1325X;
  long rest_list_1324X;
  long stack_nargs_1323X;
  long arg1_1322X;
  long arg0_1321X;
  long arg0_1320X;
  long rest_list_1319X;
  long stack_nargs_1318X;
  long x_1317X;
  long index_1316X;
  long val_1315X;
  long max_1314X;
  long p_1313X;
  char * code_pointer_1312X;
  long return_pointer_offset_1311X;
  long nargs_1310X;
  long code_1309X;
  long template_1308X;
  long rest_list_1307X;
  long stack_nargs_1306X;
  long p_1305X;
  long p_1304X;
  long cont_1303X;
  long v_1302X;
  long rest_list_1301X;
  long stack_nargs_1300X;
  long p_1299X;
  long x_1298X;
  long args_1297X;
  char * code_pointer_1296X;
  long return_pointer_offset_1295X;
  long length_1294X;
  char okayP_1293X;
  long stack_nargs_1292X;
  long list_args_1291X;
  char v_1290X;
  char v_1289X;
  long v_1288X;
  long v_1287X;
  long v_1286X;
  char * code_pointer_1285X;
  long return_pointer_offset_1284X;
  long stack_arg_count_1283X;
  long stack_arg_count_1282X;
  char * code_pointer_1281X;
  long stack_arg_count_1280X;
  long v_1279X;
  char * top_1278X;
  long arg_count_1277X;
  long n_moves_1276X;
  long x_1275X;
  long n_moves_1274X;
  long x_1273X;
  long x_1272X;
  long x_1271X;
  long x_1270X;
  long x_1269X;
  long value_1268X;
  long x_1267X;
  long closure_1266X;
  char * addr_1265X;
  long len_1264X;
  long size_1263X;
  long free_count_1262X;
  char * addr_1261X;
  long x_1260X;
  long value_1259X;
  char * addr_1258X;
  long x_1257X;
  long x_1256X;
  long template_1255X;
  long new_env_1254X;
  char * addr_1253X;
  long len_1252X;
  long closures_1251X;
  long total_count_1250X;
  long template_1249X;
  long new_env_1248X;
  char * addr_1247X;
  long len_1246X;
  long closures_1245X;
  long total_count_1244X;
  char * addr_1243X;
  long val_1242X;
  long x_1241X;
  long location_1240X;
  long index_1239X;
  long template_1238X;
  long location_1237X;
  long index_1236X;
  long template_1235X;
  long x_1234X;
  long x_1233X;
  long n_1232X;
  char * code_pointer_1231X;
  long v_1230X;
  long code_1229X;
  long n_1228X;
  char * addr_1227X;
  long x_1226X;
  long x_1225X;
  long pc_1224X;
  long code_1223X;
  long x_1222X;
  char v_1221X;
  char v_1220X;
  long tag_1219X;
  long n_1218X;
  long v_1217X;
  char v_1216X;
  long x_1215X;
  long x_1214X;
  long x_1213X;
  long x_1212X;
  long x_1211X;
  long x_1210X;
  long x_1209X;
  long x_1208X;
  long spec_1207X;
  long needed_stack_space_1206X;
  long template_1205X;
  long used_1204X;
  long code_1203X;
  long v_1202X;
  long v_1201X;
  long code_1200X;
  long n_1199X;
  char * addr_1198X;
  long x_1197X;
  long x_1196X;
  long x_1195X;
  long protocol_skip_1194X;
  long final_stack_arg_count_1193X;
  char interruptP_1192X;
  long obj_1191X;
  long template_1190X;
  char v_1189X;
  char v_1188X;
  long skip_1187X;
  long skip_1186X;
  long x_1185X;
  long x_1184X;
  long x_1183X;
  long x_1182X;
  long x_1181X;
  long x_1180X;
  long x_1179X;
  long x_1178X;
  long spec_1177X;
  long template_1176X;
  long used_1175X;
  long envUtemp_offset_1174X;
  long code_1173X;
  long retval_1172X;
  long handlers_1171X;
  long opcode_1170X;
  long nargs_1169X;
  long v_1168X;
  long v_1167X;
  long v_1166X;
  long v_1165X;
  long index_1164X;
  long length_1163X;
  long v_1162X;
  long v_1161X;
  long v_1160X;
  long v_1159X;
  long v_1158X;
  long v_1157X;
  long wants_stack_args_1156X;
  long v_1155X;
  long v_1154X;
  long v_1153X;
  long v_1152X;
  long skip_1151X;
  char nativeP_1150X;
  long stack_space_1149X;
  long protocol_1148X;
  long v_1147X;
  long x_1146X;
  long args_1145X;
  long v_1144X;
  long list_arg_count_1143X;
  long list_args_1142X;
  long stack_arg_count_1141X;
  long exception_1140X;
  long total_arg_count_1139X;
  long code_1138X;
  long handler_tag_1137X;
  long list_arg_count_1136X;
  long list_args_1135X;
  long stack_arg_count_1134X;
  long obj_1133X;
 {  if ((3 == (3 & proc_1100X))) {
    if ((3 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + proc_1100X))))), 2))))) {
      SvalS = proc_1100X;
      obj_1133X = SvalS;
      if ((3 == (3 & obj_1133X))) {
        if ((3 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_1133X))))), 2))))) {
          arg0K0 = nargs_1101X;
          arg0K1 = 25;
          arg0K2 = 0;
          arg0K3 = -1;
          goto L66500;}
        else {
          arg0K0 = 3;
          arg0K1 = nargs_1101X;
          arg0K2 = 25;
          arg0K3 = 0;
          goto L33486;}}
      else {
        arg0K0 = 3;
        arg0K1 = nargs_1101X;
        arg0K2 = 25;
        arg0K3 = 0;
        goto L33486;}}
    else {
      goto L33646;}}
  else {
    goto L33646;}}
 L66500: {
  stack_arg_count_1134X = arg0K0;
  list_args_1135X = arg0K1;
  list_arg_count_1136X = arg0K2;
  handler_tag_1137X = arg0K3;
  code_1138X = *((long *) (((char *) (-3 + (*((long *) (((char *) (-3 + (SvalS))))))))));
  total_arg_count_1139X = stack_arg_count_1134X + list_arg_count_1136X;
  arg0K0 = (*((unsigned char *) ((((char *) (-3 + code_1138X))) + 1)));
  arg0K1 = 64;
  arg4K2 = 0;
  goto L66526;}
 L33486: {
  exception_1140X = arg0K0;
  stack_arg_count_1141X = arg0K1;
  list_args_1142X = arg0K2;
  list_arg_count_1143X = arg0K3;
  merged_arg0K0 = list_args_1142X;
  merged_arg0K1 = list_arg_count_1143X;
#ifdef USE_DIRECT_THREADING
  copy_listSAgc_return_address = &&copy_listSAgc_return_0;
#else
  copy_listSAgc_return_tag = 0;
#endif
  goto copy_listSAgc;
 copy_listSAgc_return_0:
  v_1144X = copy_listSAgc0_return_value;
  merged_arg0K0 = v_1144X;
  merged_arg0K1 = stack_arg_count_1141X;
#ifdef USE_DIRECT_THREADING
  pop_args_GlistSAgc_return_address = &&pop_args_GlistSAgc_return_0;
#else
  pop_args_GlistSAgc_return_tag = 0;
#endif
  goto pop_args_GlistSAgc;
 pop_args_GlistSAgc_return_0:
  args_1145X = pop_args_GlistSAgc0_return_value;push_exception_setupB(exception_1140X, 0);
  x_1146X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_1146X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (args_1145X);
  arg0K0 = 2;
  goto L33796;}
 L33646: {
  ps_error("s48-restart called with non-procedure", 1, proc_1100X);
  return v_1147X;}
 L66526: {
  protocol_1148X = arg0K0;
  stack_space_1149X = arg0K1;
  nativeP_1150X = arg4K2;
  if ((69 == protocol_1148X)) {
    if ((total_arg_count_1139X < 3)) {
      skip_1151X = *((unsigned char *) ((((char *) (-3 + code_1138X))) + (3 + total_arg_count_1139X)));
      if ((0 == skip_1151X)) {
        if ((-1 == handler_tag_1137X)) {
          arg0K0 = 4;
          arg0K1 = stack_arg_count_1134X;
          arg0K2 = list_args_1135X;
          arg0K3 = list_arg_count_1136X;
          goto L33486;}
        else {
          if ((handler_tag_1137X < 0)) {
            ps_error("wrong number of arguments to interrupt handler", 1, (-2 - handler_tag_1137X));
            arg0K0 = v_1152X;
            goto L70968;}
          else {
            ps_error("wrong number of arguments to exception handler", 1, handler_tag_1137X);
            arg0K0 = v_1153X;
            goto L70968;}}}
      else {
        merged_arg0K0 = list_args_1135X;
        merged_arg0K1 = list_arg_count_1136X;
#ifdef USE_DIRECT_THREADING
        push_list_return_address = &&push_list_return_0;
#else
        push_list_return_tag = 0;
#endif
        goto push_list;
       push_list_return_0:
        arg0K0 = code_1138X;
        arg0K1 = 6;
        arg0K2 = skip_1151X;
        arg0K3 = (*((long *) (((char *) (-3 + (SvalS))))));
        goto L32468;}}
    else {
      if ((0 == (*((unsigned char *) ((((char *) (-3 + code_1138X))) + 2))))) {
        if ((-1 == handler_tag_1137X)) {
          arg0K0 = 4;
          arg0K1 = stack_arg_count_1134X;
          arg0K2 = list_args_1135X;
          arg0K3 = list_arg_count_1136X;
          goto L33486;}
        else {
          if ((handler_tag_1137X < 0)) {
            ps_error("wrong number of arguments to interrupt handler", 1, (-2 - handler_tag_1137X));
            arg0K0 = v_1154X;
            goto L70968;}
          else {
            ps_error("wrong number of arguments to exception handler", 1, handler_tag_1137X);
            arg0K0 = v_1155X;
            goto L70968;}}}
      else {
        arg0K0 = 6;
        goto L66568;}}}
  else {
    if ((63 < protocol_1148X)) {
      if ((65 == protocol_1148X)) {
        wants_stack_args_1156X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((((char *) (-3 + code_1138X))) + 2))), 8)) + (*((unsigned char *) ((((char *) (-3 + code_1138X))) + 3)));
        if ((total_arg_count_1139X < wants_stack_args_1156X)) {
          if ((-1 == handler_tag_1137X)) {
            arg0K0 = 4;
            arg0K1 = stack_arg_count_1134X;
            arg0K2 = list_args_1135X;
            arg0K3 = list_arg_count_1136X;
            goto L33486;}
          else {
            if ((handler_tag_1137X < 0)) {
              ps_error("wrong number of arguments to interrupt handler", 1, (-2 - handler_tag_1137X));
              arg0K0 = v_1157X;
              goto L70968;}
            else {
              ps_error("wrong number of arguments to exception handler", 1, handler_tag_1137X);
              arg0K0 = v_1158X;
              goto L70968;}}}
        else {
          merged_arg0K0 = wants_stack_args_1156X;
          merged_arg0K1 = stack_arg_count_1134X;
          merged_arg0K2 = list_args_1135X;
          merged_arg0K3 = list_arg_count_1136X;
#ifdef USE_DIRECT_THREADING
          rest_list_setupAgc_return_address = &&rest_list_setupAgc_return_0;
#else
          rest_list_setupAgc_return_tag = 0;
#endif
          goto rest_list_setupAgc;
         rest_list_setupAgc_return_0:
          arg0K0 = 4;
          goto L66529;}}
      else {
        if ((68 == protocol_1148X)) {
          if ((total_arg_count_1139X < (*((unsigned char *) ((((char *) (-3 + code_1138X))) + 2))))) {
            if ((-1 == handler_tag_1137X)) {
              arg0K0 = 4;
              arg0K1 = stack_arg_count_1134X;
              arg0K2 = list_args_1135X;
              arg0K3 = list_arg_count_1136X;
              goto L33486;}
            else {
              if ((handler_tag_1137X < 0)) {
                ps_error("wrong number of arguments to interrupt handler", 1, (-2 - handler_tag_1137X));
                arg0K0 = v_1159X;
                goto L70968;}
              else {
                ps_error("wrong number of arguments to exception handler", 1, handler_tag_1137X);
                arg0K0 = v_1160X;
                goto L70968;}}}
          else {
            arg0K0 = 3;
            goto L66568;}}
        else {
          if ((127 < protocol_1148X)) {
            arg0K0 = (127 & protocol_1148X);
            arg0K1 = stack_space_1149X;
            arg4K2 = 1;
            goto L66526;}
          else {
            if ((64 == protocol_1148X)) {
              if ((((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((((char *) (-3 + code_1138X))) + 2))), 8)) + (*((unsigned char *) ((((char *) (-3 + code_1138X))) + 3)))) == total_arg_count_1139X)) {
                if ((0 == list_arg_count_1136X)) {
                  arg0K0 = 4;
                  goto L66529;}
                else {
                  merged_arg0K0 = list_args_1135X;
                  merged_arg0K1 = list_arg_count_1136X;
#ifdef USE_DIRECT_THREADING
                  push_list_return_address = &&push_list_return_1;
#else
                  push_list_return_tag = 1;
#endif
                  goto push_list;
                 push_list_return_1:
                  arg0K0 = 4;
                  goto L66529;}}
              else {
                if ((-1 == handler_tag_1137X)) {
                  arg0K0 = 4;
                  arg0K1 = stack_arg_count_1134X;
                  arg0K2 = list_args_1135X;
                  arg0K3 = list_arg_count_1136X;
                  goto L33486;}
                else {
                  if ((handler_tag_1137X < 0)) {
                    ps_error("wrong number of arguments to interrupt handler", 1, (-2 - handler_tag_1137X));
                    arg0K0 = v_1161X;
                    goto L70968;}
                  else {
                    ps_error("wrong number of arguments to exception handler", 1, handler_tag_1137X);
                    arg0K0 = v_1162X;
                    goto L70968;}}}}
            else {
              if ((67 == protocol_1148X)) {
                length_1163X = PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + code_1138X))))), 8);
                index_1164X = -2 + length_1163X;
                arg0K0 = (*((unsigned char *) ((((char *) (-3 + code_1138X))) + (-3 + length_1163X))));
                arg0K1 = ((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((((char *) (-3 + code_1138X))) + index_1164X))), 8)) + (*((unsigned char *) ((((char *) (-3 + code_1138X))) + (1 + index_1164X)))));
                arg4K2 = nativeP_1150X;
                goto L66526;}
              else {
                ps_error("unknown protocol", 1, protocol_1148X);
                if ((-1 == handler_tag_1137X)) {
                  arg0K0 = 4;
                  arg0K1 = stack_arg_count_1134X;
                  arg0K2 = list_args_1135X;
                  arg0K3 = list_arg_count_1136X;
                  goto L33486;}
                else {
                  if ((handler_tag_1137X < 0)) {
                    ps_error("wrong number of arguments to interrupt handler", 1, (-2 - handler_tag_1137X));
                    arg0K0 = v_1165X;
                    goto L70968;}
                  else {
                    ps_error("wrong number of arguments to exception handler", 1, handler_tag_1137X);
                    arg0K0 = v_1166X;
                    goto L70968;}}}}}}}}
    else {
      if ((protocol_1148X == total_arg_count_1139X)) {
        if ((0 == list_arg_count_1136X)) {
          arg0K0 = 2;
          goto L66529;}
        else {
          merged_arg0K0 = list_args_1135X;
          merged_arg0K1 = list_arg_count_1136X;
#ifdef USE_DIRECT_THREADING
          push_list_return_address = &&push_list_return_2;
#else
          push_list_return_tag = 2;
#endif
          goto push_list;
         push_list_return_2:
          arg0K0 = 2;
          goto L66529;}}
      else {
        if ((-1 == handler_tag_1137X)) {
          arg0K0 = 4;
          arg0K1 = stack_arg_count_1134X;
          arg0K2 = list_args_1135X;
          arg0K3 = list_arg_count_1136X;
          goto L33486;}
        else {
          if ((handler_tag_1137X < 0)) {
            ps_error("wrong number of arguments to interrupt handler", 1, (-2 - handler_tag_1137X));
            arg0K0 = v_1167X;
            goto L70968;}
          else {
            ps_error("wrong number of arguments to exception handler", 1, handler_tag_1137X);
            arg0K0 = v_1168X;
            goto L70968;}}}}}}
 L33796: {
  nargs_1169X = arg0K0;
  opcode_1170X = PS_SHIFT_RIGHT_INLINE((*((long *) ((SstackS) + (8 + (PS_SHIFT_LEFT_INLINE(nargs_1169X, 3)))))), 2);
  handlers_1171X = SHARED_REF((Sexception_handlersS));
  if ((3 == (3 & handlers_1171X))) {
    if ((2 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + handlers_1171X))))), 2))))) {
      goto L33861;}
    else {
      goto L33944;}}
  else {
    goto L33944;}}
 L70968: {
  retval_1172X = arg0K0;
  SstackS = (ScontS);
  return retval_1172X;}
 L32468: {
  code_1173X = arg0K0;
  envUtemp_offset_1174X = arg0K1;
  used_1175X = arg0K2;
  template_1176X = arg0K3;
  spec_1177X = *((unsigned char *) ((((char *) (-3 + code_1173X))) + envUtemp_offset_1174X));
  if ((3 == spec_1177X)) {
    x_1178X = *((long *) ((((char *) (-3 + (SvalS)))) + 8));
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (x_1178X);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (template_1176X);
    goto L32472;}
  else {
    if ((1 == spec_1177X)) {
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (template_1176X);
      goto L32472;}
    else {
      if ((2 == spec_1177X)) {
        x_1179X = *((long *) ((((char *) (-3 + (SvalS)))) + 8));
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1179X);
        goto L32472;}
      else {
        if ((4 == spec_1177X)) {
          x_1180X = SvalS;
          SstackS = ((SstackS) + -8);
          *((long *) (SstackS)) = (long) (x_1180X);
          goto L32472;}
        else {
          if ((6 == spec_1177X)) {
            x_1181X = SvalS;
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (x_1181X);
            x_1182X = *((long *) ((((char *) (-3 + (SvalS)))) + 8));
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (x_1182X);
            goto L32472;}
          else {
            if ((5 == spec_1177X)) {
              x_1183X = SvalS;
              SstackS = ((SstackS) + -8);
              *((long *) (SstackS)) = (long) (x_1183X);
              SstackS = ((SstackS) + -8);
              *((long *) (SstackS)) = (long) (template_1176X);
              goto L32472;}
            else {
              if ((7 == spec_1177X)) {
                x_1184X = SvalS;
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) (x_1184X);
                x_1185X = *((long *) ((((char *) (-3 + (SvalS)))) + 8));
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) (x_1185X);
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) (template_1176X);
                goto L32472;}
              else {
                goto L32472;}}}}}}}}
 L66568: {
  skip_1186X = arg0K0;
  if ((total_arg_count_1139X < 3)) {
    arg0K0 = total_arg_count_1139X;
    goto L66576;}
  else {
    if ((2 < stack_arg_count_1134X)) {
      arg0K0 = stack_arg_count_1134X;
      goto L66576;}
    else {
      arg0K0 = 2;
      goto L66576;}}}
 L66529: {
  skip_1187X = arg0K0;
  if (nativeP_1150X) {
    merged_arg0K0 = stack_space_1149X;
#ifdef USE_DIRECT_THREADING
    ensure_stack_spaceB_return_address = &&ensure_stack_spaceB_return_0;
#else
    ensure_stack_spaceB_return_tag = 0;
#endif
    goto ensure_stack_spaceB;
   ensure_stack_spaceB_return_0:
    v_1188X = ensure_stack_spaceB0_return_value;
    if (v_1188X) {
#ifdef USE_DIRECT_THREADING
      pending_interruptP_return_address = &&pending_interruptP_return_0;
#else
      pending_interruptP_return_tag = 0;
#endif
      goto pending_interruptP;
     pending_interruptP_return_0:
      v_1189X = pending_interruptP0_return_value;
      if (v_1189X) {
        arg0K0 = skip_1187X;
        goto L33084;}
      else {
        goto L66696;}}
    else {
      goto L66696;}}
  else {
    template_1190X = *((long *) (((char *) (-3 + (SvalS)))));
    arg0K0 = (*((long *) (((char *) (-3 + template_1190X)))));
    arg0K1 = skip_1187X;
    arg0K2 = template_1190X;
    arg0K3 = stack_space_1149X;
    goto L36681;}}
 L33861: {
  SvalS = (*((long *) ((((char *) (-3 + handlers_1171X))) + (PS_SHIFT_LEFT_INLINE(opcode_1170X, 3)))));
  obj_1191X = SvalS;
  if ((3 == (3 & obj_1191X))) {
    if ((3 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_1191X))))), 2))))) {
      goto L33878;}
    else {
      goto L33958;}}
  else {
    goto L33958;}}
 L33944: {
  merged_arg5K0 = "exception-handlers is not a vector";
#ifdef USE_DIRECT_THREADING
  loseD0_return_address = &&loseD0_return_0;
#else
  loseD0_return_tag = 0;
#endif
  goto loseD0;
 loseD0_return_0:
  goto L33861;}
 L32472: {
  Slast_code_calledS = code_1173X;
  Scode_pointerS = ((((char *) (-3 + code_1173X))) + used_1175X);
  if (((SstackS) < (s48_Sstack_limitS))) {
    interruptP_1192X = (s48_Sstack_limitS) == (((char *) -1));
    s48_Sstack_limitS = (Sreal_stack_limitS);
    if (((SstackS) < (Sreal_stack_limitS))) {s48_copy_stack_into_heap();
      if (((SstackS) < (Sreal_stack_limitS))) {
        ps_error("VM's stack is too small (how can this happen?)", 0);
        if (interruptP_1192X) {
          goto L32479;}
        else {
          goto L32486;}}
      else {
        if (interruptP_1192X) {
          goto L32479;}
        else {
          goto L32486;}}}
    else {
      if (interruptP_1192X) {
        goto L32479;}
      else {
        goto L32486;}}}
  else {
    goto L32486;}}
 L66576: {
  final_stack_arg_count_1193X = arg0K0;
  if ((stack_arg_count_1134X < final_stack_arg_count_1193X)) {
    arg0K0 = final_stack_arg_count_1193X;
    goto L66580;}
  else {
    arg0K0 = stack_arg_count_1134X;
    goto L66580;}}
 L33084: {
  protocol_skip_1194X = arg0K0;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(protocol_skip_1194X, 2)));
  x_1195X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_1195X);
  x_1196X = *((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_1196X);
  x_1197X = Scurrent_threadS;
  addr_1198X = (((char *) (-3 + x_1197X))) + 24;S48_WRITE_BARRIER(x_1197X, addr_1198X, 1);
  *((long *) addr_1198X) = (long) (1);
  n_1199X = Senabled_interruptsS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(n_1199X, 2)));
  code_1200X = Sinterrupted_native_call_return_codeS;
  v_1201X = PS_SHIFT_RIGHT_INLINE(((ScontS) - (SstackS)), 3);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((4 + (PS_SHIFT_LEFT_INLINE(v_1201X, 2))));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((((long) ((((char *) (-3 + code_1200X))) + 13))));
  ScontS = (SstackS);
  goto L32818;}
 L66696: {
  v_1202X = s48_call_native_procedure((SvalS), skip_1187X);
  arg0K0 = v_1202X;
  goto L65708;}
 L36681: {
  code_1203X = arg0K0;
  used_1204X = arg0K1;
  template_1205X = arg0K2;
  needed_stack_space_1206X = arg0K3;
  spec_1207X = *((unsigned char *) ((((char *) (-3 + code_1203X))) + used_1204X));
  if ((3 == spec_1207X)) {
    x_1208X = *((long *) ((((char *) (-3 + (SvalS)))) + 8));
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (x_1208X);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (template_1205X);
    goto L36685;}
  else {
    if ((1 == spec_1207X)) {
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (template_1205X);
      goto L36685;}
    else {
      if ((2 == spec_1207X)) {
        x_1209X = *((long *) ((((char *) (-3 + (SvalS)))) + 8));
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1209X);
        goto L36685;}
      else {
        if ((4 == spec_1207X)) {
          x_1210X = SvalS;
          SstackS = ((SstackS) + -8);
          *((long *) (SstackS)) = (long) (x_1210X);
          goto L36685;}
        else {
          if ((6 == spec_1207X)) {
            x_1211X = SvalS;
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (x_1211X);
            x_1212X = *((long *) ((((char *) (-3 + (SvalS)))) + 8));
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (x_1212X);
            goto L36685;}
          else {
            if ((5 == spec_1207X)) {
              x_1213X = SvalS;
              SstackS = ((SstackS) + -8);
              *((long *) (SstackS)) = (long) (x_1213X);
              SstackS = ((SstackS) + -8);
              *((long *) (SstackS)) = (long) (template_1205X);
              goto L36685;}
            else {
              if ((7 == spec_1207X)) {
                x_1214X = SvalS;
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) (x_1214X);
                x_1215X = *((long *) ((((char *) (-3 + (SvalS)))) + 8));
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) (x_1215X);
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) (template_1205X);
                goto L36685;}
              else {
                goto L36685;}}}}}}}}
 L33878: {
  arg0K0 = (2 + nargs_1169X);
  arg0K1 = 25;
  arg0K2 = 0;
  arg0K3 = opcode_1170X;
  goto L66500;}
 L33958: {
  merged_arg5K0 = "exception handler is not a closure";
#ifdef USE_DIRECT_THREADING
  loseD0_return_address = &&loseD0_return_1;
#else
  loseD0_return_tag = 1;
#endif
  goto loseD0;
 loseD0_return_1:
  goto L33878;}
 L32479: {

#ifdef USE_DIRECT_THREADING
  pending_interruptP_return_address = &&pending_interruptP_return_1;
#else
  pending_interruptP_return_tag = 1;
#endif
  goto pending_interruptP;
 pending_interruptP_return_1:
  v_1216X = pending_interruptP0_return_value;
  if (v_1216X) {
    goto L32995;}
  else {
    goto L32486;}}
 L32486: {
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L66580: {
  v_1217X = arg0K0;
  merged_arg0K0 = v_1217X;
  merged_arg0K1 = stack_arg_count_1134X;
  merged_arg0K2 = list_args_1135X;
  merged_arg0K3 = list_arg_count_1136X;
#ifdef USE_DIRECT_THREADING
  rest_list_setupAgc_return_address = &&rest_list_setupAgc_return_1;
#else
  rest_list_setupAgc_return_tag = 1;
#endif
  goto rest_list_setupAgc;
 rest_list_setupAgc_return_1:
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(final_stack_arg_count_1193X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(total_arg_count_1139X, 2)));
  arg0K0 = skip_1186X;
  goto L66529;}
 L32818: {
  n_1218X = (Spending_interruptsS) & (Senabled_interruptsS);
  arg0K0 = 0;
  arg0K1 = 1;
  goto L32871;}
 L65708: {
  tag_1219X = arg0K0;
  arg0K0 = tag_1219X;
  goto L65712;}
 L36685: {
  Slast_code_calledS = code_1203X;
  Scode_pointerS = ((((char *) (-3 + code_1203X))) + (1 + used_1204X));
  merged_arg0K0 = needed_stack_space_1206X;
#ifdef USE_DIRECT_THREADING
  ensure_stack_spaceB_return_address = &&ensure_stack_spaceB_return_1;
#else
  ensure_stack_spaceB_return_tag = 1;
#endif
  goto ensure_stack_spaceB;
 ensure_stack_spaceB_return_1:
  v_1220X = ensure_stack_spaceB0_return_value;
  if (v_1220X) {
#ifdef USE_DIRECT_THREADING
    pending_interruptP_return_address = &&pending_interruptP_return_2;
#else
    pending_interruptP_return_tag = 2;
#endif
    goto pending_interruptP;
   pending_interruptP_return_2:
    v_1221X = pending_interruptP0_return_value;
    if (v_1221X) {
      goto L32995;}
    else {
      goto L36699;}}
  else {
    goto L36699;}}
 L32995: {
  x_1222X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_1222X);
  code_1223X = current_code_vector();
  pc_1224X = (Scode_pointerS) - (((char *) (-3 + code_1223X)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (code_1223X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(pc_1224X, 2)));
  x_1225X = *((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_1225X);
  x_1226X = Scurrent_threadS;
  addr_1227X = (((char *) (-3 + x_1226X))) + 24;S48_WRITE_BARRIER(x_1226X, addr_1227X, 1);
  *((long *) addr_1227X) = (long) (1);
  n_1228X = Senabled_interruptsS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(n_1228X, 2)));
  code_1229X = Sinterrupted_byte_opcode_return_codeS;
  v_1230X = PS_SHIFT_RIGHT_INLINE(((ScontS) - (SstackS)), 3);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((4 + (PS_SHIFT_LEFT_INLINE(v_1230X, 2))));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((((long) ((((char *) (-3 + code_1229X))) + 13))));
  ScontS = (SstackS);
  goto L32818;}
 L36237: {
  code_pointer_1231X = arg3K0;
#ifdef USE_DIRECT_THREADING
  static void *Jtable36237[] = { &&Jlabel36237_0, 
    &&Jlabel36237_1, &&Jlabel36237_2, &&Jlabel36237_3, &&Jlabel36237_4, &&Jlabel36237_5, &&Jlabel36237_6, 
    &&Jlabel36237_7, &&Jlabel36237_8, &&Jlabel36237_9, &&Jlabel36237_10, &&Jlabel36237_11, &&Jlabel36237_12, 
    &&Jlabel36237_13, &&Jlabel36237_14, &&Jlabel36237_15, &&Jlabel36237_16, &&Jlabel36237_17, &&Jlabel36237_18, 
    &&Jlabel36237_19, &&Jlabel36237_20, &&Jlabel36237_21, &&Jlabel36237_22, &&Jlabel36237_23, &&Jlabel36237_24, 
    &&Jlabel36237_25, &&Jlabel36237_26, &&Jlabel36237_27, &&Jlabel36237_28, &&Jlabel36237_29, &&Jlabel36237_30, 
    &&Jlabel36237_31, &&Jlabel36237_32, &&Jlabel36237_33, &&Jlabel36237_34, &&Jlabel36237_35, &&Jlabel36237_36, 
    &&Jlabel36237_37, &&Jlabel36237_38, &&Jlabel36237_39, &&Jlabel36237_40, &&Jlabel36237_41, &&Jlabel36237_42, 
    &&Jlabel36237_43, &&Jlabel36237_44, &&Jlabel36237_45, &&Jlabel36237_46, &&Jlabel36237_47, &&Jlabel36237_48, 
    &&Jlabel36237_49, &&Jlabel36237_50, &&Jlabel36237_51, &&Jlabel36237_52, &&Jlabel36237_53, &&Jlabel36237_54, 
    &&Jlabel36237_55, &&Jlabel36237_56, &&Jlabel36237_57, &&Jlabel36237_58, &&Jlabel36237_59, &&Jlabel36237_60, 
    &&Jlabel36237_61, &&Jlabel36237_62, &&Jlabel36237_63, &&Jlabel36237_64, &&Jlabel36237_65, &&Jlabel36237_66, 
    &&Jlabel36237_67, &&Jlabel36237_68, &&Jlabel36237_69, &&Jlabel36237_70, &&Jlabel36237_71, &&Jlabel36237_72, 
    &&Jlabel36237_73, &&Jlabel36237_74, &&Jlabel36237_75, &&Jlabel36237_76, &&Jlabel36237_77, &&Jlabel36237_78, 
    &&Jlabel36237_79, &&Jlabel36237_80, &&Jlabel36237_81, &&Jlabel36237_82, &&Jlabel36237_83, &&Jlabel36237_84, 
    &&Jlabel36237_85, &&Jlabel36237_86, &&Jlabel36237_87, &&Jlabel36237_88, &&Jlabel36237_89, &&Jlabel36237_90, 
    &&Jlabel36237_91, &&Jlabel36237_92, &&Jlabel36237_93, &&Jlabel36237_94, &&Jlabel36237_95, &&Jlabel36237_96, 
    &&Jlabel36237_97, &&Jlabel36237_98, &&Jlabel36237_99, &&Jlabel36237_100, &&Jlabel36237_101, &&Jlabel36237_102, 
    &&Jlabel36237_103, &&Jlabel36237_104, &&Jlabel36237_105, &&Jlabel36237_106, &&Jlabel36237_107, &&Jlabel36237_108, 
    &&Jlabel36237_109, &&Jlabel36237_110, &&Jlabel36237_111, &&Jlabel36237_112, &&Jlabel36237_113, &&Jlabel36237_114, 
    &&Jlabel36237_115, &&Jlabel36237_116, &&Jlabel36237_117, &&Jlabel36237_118, &&Jlabel36237_119, &&Jlabel36237_120, 
    &&Jlabel36237_121, &&Jlabel36237_122, &&Jlabel36237_123, &&Jlabel36237_124, &&Jlabel36237_125, &&Jlabel36237_126, 
    &&Jlabel36237_127, &&Jlabel36237_128, &&Jlabel36237_129, &&Jlabel36237_130, &&Jlabel36237_131, &&Jlabel36237_132, 
    &&Jlabel36237_133, &&Jlabel36237_134, &&Jlabel36237_135, &&Jlabel36237_136, &&Jlabel36237_137, &&Jlabel36237_138, 
    &&Jlabel36237_139, &&Jlabel36237_140, &&Jlabel36237_141, &&Jlabel36237_142, &&Jlabel36237_143, &&Jlabel36237_144, 
    &&Jlabel36237_145, &&Jlabel36237_146, &&Jlabel36237_147, &&Jlabel36237_148, &&Jlabel36237_149, &&Jlabel36237_150, 
    &&Jlabel36237_151, &&Jlabel36237_152, &&Jlabel36237_153, &&Jlabel36237_154, &&Jlabel36237_155, &&Jlabel36237_156, 
    &&Jlabel36237_157, &&Jlabel36237_158, &&Jlabel36237_159, &&Jlabel36237_160, &&Jlabel36237_161, &&Jlabel36237_162, 
    &&Jlabel36237_163, &&Jlabel36237_164, &&Jlabel36237_165, &&Jlabel36237_166, &&Jlabel36237_167, &&Jlabel36237_168, 
    &&Jlabel36237_169, &&Jlabel36237_170, &&Jlabel36237_171, &&Jlabel36237_172, &&Jlabel36237_173, &&Jlabel36237_174, 
    &&Jlabel36237_175, &&Jlabel36237_176, &&Jlabel36237_177, &&Jlabel36237_178, &&Jlabel36237_179, &&Jlabel36237_180, 
    &&Jlabel36237_181, &&Jlabel36237_182, &&Jlabel36237_183, &&Jlabel36237_184, &&Jlabel36237_185, &&Jlabel36237_186, 
    &&Jlabel36237_187, &&Jlabel36237_188, &&Jlabel36237_189, &&Jlabel36237_190, &&Jlabel36237_191, &&Jlabel36237_192, 
    &&Jlabel36237_193, &&Jlabel36237_194, &&Jlabel36237_195, &&Jlabel36237_196, &&Jlabel36237_197, &&Jlabel36237_198, 
    &&Jlabel36237_199, &&Jlabel36237_200, &&Jlabel36237_201, &&Jlabel36237_202, &&Jlabel36237_203, &&Jlabel36237_204 };
  goto *Jtable36237[(*((unsigned char *) code_pointer_1231X))];
#else
  switch ((*((unsigned char *) code_pointer_1231X))) {
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_0:
Jlabel36237_31:
Jlabel36237_45:
Jlabel36237_141:
#else
    case 0 : 
    case 31 : 
    case 45 : 
    case 141 : 
#endif
      {push_exception_setupB(15, 1);
      n_1232X = *((unsigned char *) (Scode_pointerS));
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(n_1232X, 2)));
      arg0K0 = 1;
      goto L33796;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_1:
#else
    case 1 : 
#endif
      {
      SvalS = (-512 + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 2)));
      Scode_pointerS = ((Scode_pointerS) + 2);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_2:
#else
    case 2 : 
#endif
      {
      x_1233X = SvalS;
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1233X);
      SvalS = (-512 + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 2)));
      Scode_pointerS = ((Scode_pointerS) + 2);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_3:
#else
    case 3 : 
#endif
      {
      x_1234X = -512 + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 2));
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1234X);
      Scode_pointerS = ((Scode_pointerS) + 2);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_4:
#else
    case 4 : 
#endif
      {
      template_1235X = *((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2)))), 3))));
      index_1236X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 3))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 4)));
      location_1237X = *((long *) ((((char *) (-3 + template_1235X))) + (PS_SHIFT_LEFT_INLINE(index_1236X, 3))));
      SvalS = (*((long *) ((((char *) (-3 + location_1237X))) + 8)));
      if ((17 == (255 & (SvalS)))) {push_exception_setupB(1, 5);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (location_1237X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (template_1235X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(index_1236X, 2)));
        arg0K0 = 3;
        goto L33796;}
      else {
        Scode_pointerS = ((Scode_pointerS) + 5);
        arg3K0 = (Scode_pointerS);
        goto L36237;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_5:
#else
    case 5 : 
#endif
      {
      template_1238X = *((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2)))), 3))));
      index_1239X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 3))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 4)));
      location_1240X = *((long *) ((((char *) (-3 + template_1238X))) + (PS_SHIFT_LEFT_INLINE(index_1239X, 3))));
      if ((273 == (*((long *) ((((char *) (-3 + location_1240X))) + 8))))) {push_exception_setupB(1, 5);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (location_1240X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (template_1238X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(index_1239X, 2)));
        x_1241X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1241X);
        arg0K0 = 4;
        goto L33796;}
      else {
        val_1242X = SvalS;
        addr_1243X = (((char *) (-3 + location_1240X))) + 8;S48_WRITE_BARRIER(location_1240X, addr_1243X, val_1242X);
        *((long *) addr_1243X) = (long) (val_1242X);
        SvalS = 13;
        Scode_pointerS = ((Scode_pointerS) + 5);
        arg3K0 = (Scode_pointerS);
        goto L36237;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_6:
#else
    case 6 : 
#endif
      {
      total_count_1244X = *((unsigned char *) ((Scode_pointerS) + 1));
      closures_1245X = *((unsigned char *) ((Scode_pointerS) + 2));s48_make_availableAgc((PS_SHIFT_LEFT_INLINE(((1 + total_count_1244X) + (3 * closures_1245X)), 3)));
      len_1246X = PS_SHIFT_LEFT_INLINE(total_count_1244X, 3);
      addr_1247X = s48_allocate_small((8 + len_1246X));
      *((long *) addr_1247X) = (long) ((10 + (PS_SHIFT_LEFT_INLINE(len_1246X, 8))));
      new_env_1248X = 3 + (((long) (addr_1247X + 8)));
      if ((0 == closures_1245X)) {
        arg0K0 = new_env_1248X;
        arg0K1 = 0;
        arg0K2 = 2;
        arg0K3 = total_count_1244X;
        goto L14603;}
      else {
        template_1249X = *((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 3))), 3))));
        arg0K0 = closures_1245X;
        arg0K1 = 0;
        arg0K2 = 3;
        goto L25059;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_7:
#else
    case 7 : 
#endif
      {
      total_count_1250X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2)));
      closures_1251X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 3))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 4)));s48_make_availableAgc((PS_SHIFT_LEFT_INLINE(((1 + total_count_1250X) + (3 * closures_1251X)), 3)));
      len_1252X = PS_SHIFT_LEFT_INLINE(total_count_1250X, 3);
      addr_1253X = s48_allocate_small((8 + len_1252X));
      *((long *) addr_1253X) = (long) ((10 + (PS_SHIFT_LEFT_INLINE(len_1252X, 8))));
      new_env_1254X = 3 + (((long) (addr_1253X + 8)));
      if ((0 == closures_1251X)) {
        arg0K0 = new_env_1254X;
        arg0K1 = 0;
        arg0K2 = 4;
        arg0K3 = total_count_1250X;
        goto L15398;}
      else {
        template_1255X = *((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 5))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 6)))), 3))));
        arg0K0 = closures_1251X;
        arg0K1 = 0;
        arg0K2 = 6;
        goto L25135;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_8:
#else
    case 8 : 
#endif
      {
      x_1256X = SvalS;
      x_1257X = *((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 3))));
      addr_1258X = (((char *) (-3 + x_1257X))) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 2))), 3));S48_WRITE_BARRIER(x_1257X, addr_1258X, x_1256X);
      *((long *) addr_1258X) = (long) (x_1256X);
      SvalS = 13;
      Scode_pointerS = ((Scode_pointerS) + 3);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_9:
#else
    case 9 : 
#endif
      {
      value_1259X = SvalS;
      x_1260X = *((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2)))), 3))));
      addr_1261X = (((char *) (-3 + x_1260X))) + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 2))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 3)))), 3));S48_WRITE_BARRIER(x_1260X, addr_1261X, value_1259X);
      *((long *) addr_1261X) = (long) (value_1259X);
      SvalS = 13;
      Scode_pointerS = ((Scode_pointerS) + 5);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_10:
#else
    case 10 : 
#endif
      {
      SvalS = (*((long *) ((((char *) (-3 + (*((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 3)))))))) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 2))), 3)))));
      Scode_pointerS = ((Scode_pointerS) + 3);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_11:
#else
    case 11 : 
#endif
      {
      SvalS = (*((long *) ((((char *) (-3 + (*((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2)))), 3)))))))) + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 3))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 4)))), 3)))));
      Scode_pointerS = ((Scode_pointerS) + 5);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_12:
#else
    case 12 : 
#endif
      {
      free_count_1262X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2)));
      size_1263X = 1 + free_count_1262X;s48_make_availableAgc((8 + (PS_SHIFT_LEFT_INLINE(size_1263X, 3))));
      len_1264X = PS_SHIFT_LEFT_INLINE(size_1263X, 3);
      addr_1265X = s48_allocate_small((8 + len_1264X));
      *((long *) addr_1265X) = (long) ((14 + (PS_SHIFT_LEFT_INLINE(len_1264X, 8))));
      closure_1266X = 3 + (((long) (addr_1265X + 8)));
      *((long *) (((char *) (-3 + closure_1266X)))) = (long) ((SvalS));
      arg0K0 = free_count_1262X;
      goto L38888;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_13:
#else
    case 13 : 
#endif
      {
      x_1267X = SvalS;
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1267X);
      Scode_pointerS = ((Scode_pointerS) + 1);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_14:
#else
    case 14 : 
#endif
      {
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (1);
      Scode_pointerS = ((Scode_pointerS) + 1);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_15:
#else
    case 15 : 
#endif
      {
      value_1268X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      SvalS = value_1268X;
      Scode_pointerS = ((Scode_pointerS) + 1);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_16:
#else
    case 16 : 
#endif
      {
      SstackS = ((SstackS) + (0 - (PS_SHIFT_LEFT_INLINE((0 - ((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2))))), 3))));
      Scode_pointerS = ((Scode_pointerS) + 3);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_17:
#else
    case 17 : 
#endif
      {
      arg0K0 = ((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2))));
      goto L67265;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_18:
#else
    case 18 : 
#endif
      {
      SvalS = (*((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 3)))));
      Scode_pointerS = ((Scode_pointerS) + 2);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_19:
#else
    case 19 : 
#endif
      {
      x_1269X = SvalS;
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1269X);
      SvalS = (*((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 3)))));
      Scode_pointerS = ((Scode_pointerS) + 2);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_20:
#else
    case 20 : 
#endif
      {
      x_1270X = *((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 3))));
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1270X);
      Scode_pointerS = ((Scode_pointerS) + 2);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_21:
#else
    case 21 : 
#endif
      {
      SvalS = (*((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2)))), 3)))));
      Scode_pointerS = ((Scode_pointerS) + 3);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_22:
#else
    case 22 : 
#endif
      {
      *((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 3)))) = (long) ((SvalS));
      Scode_pointerS = ((Scode_pointerS) + 2);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_23:
#else
    case 23 : 
#endif
      {
      *((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2)))), 3)))) = (long) ((SvalS));
      Scode_pointerS = ((Scode_pointerS) + 3);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_24:
#else
    case 24 : 
#endif
      {
      SvalS = (*((long *) ((((char *) (-3 + (*((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 3)))))))) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 2))), 3)))));
      Scode_pointerS = ((Scode_pointerS) + 3);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_25:
#else
    case 25 : 
#endif
      {
      x_1271X = SvalS;
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1271X);
      SvalS = (*((long *) ((((char *) (-3 + (*((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 3)))))))) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 2))), 3)))));
      Scode_pointerS = ((Scode_pointerS) + 3);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_26:
#else
    case 26 : 
#endif
      {
      x_1272X = *((long *) ((((char *) (-3 + (*((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 3)))))))) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 2))), 3))));
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1272X);
      Scode_pointerS = ((Scode_pointerS) + 3);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_27:
#else
    case 27 : 
#endif
      {
      SvalS = (*((long *) ((((char *) (-3 + (*((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2)))), 3)))))))) + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 3))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 4)))), 3)))));
      Scode_pointerS = ((Scode_pointerS) + 5);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_28:
#else
    case 28 : 
#endif
      {
      x_1273X = SvalS;
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1273X);
      n_moves_1274X = *((unsigned char *) ((Scode_pointerS) + 1));
      arg0K0 = 0;
      goto L38222;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_29:
#else
    case 29 : 
#endif
      {
      x_1275X = SvalS;
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1275X);
      n_moves_1276X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2)));
      arg0K0 = 0;
      goto L38139;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_30:
#else
    case 30 : 
#endif
      {s48_make_availableAgc((PS_SHIFT_LEFT_INLINE((-4 & (PS_SHIFT_RIGHT_INLINE(((Sstack_endS) - (SstackS)), 1))), 3)));
      arg_count_1277X = PS_SHIFT_RIGHT_INLINE(((ScontS) - (SstackS)), 3);
      top_1278X = SstackS;
      if ((1 == (((long) (ScontS))))) {
        arg0K0 = 1;
        goto L31400;}
      else {
        v_1279X = really_preserve_continuation(0);
        arg0K0 = v_1279X;
        goto L31400;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_32:
#else
    case 32 : 
#endif
      {
      stack_arg_count_1280X = *((unsigned char *) ((Scode_pointerS) + 3));
      code_pointer_1281X = (Scode_pointerS) + ((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2))));
      ScontS = ((SstackS) + (PS_SHIFT_LEFT_INLINE(stack_arg_count_1280X, 3)));
      *((long *) (ScontS)) = (long) ((((long) code_pointer_1281X)));
      arg0K0 = stack_arg_count_1280X;
      goto L66427;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_33:
#else
    case 33 : 
#endif
      {
      stack_arg_count_1282X = *((unsigned char *) ((Scode_pointerS) + 1));
      merged_arg0K0 = stack_arg_count_1282X;
#ifdef USE_DIRECT_THREADING
      move_args_above_contB_return_address = &&move_args_above_contB_return_0;
#else
      move_args_above_contB_return_tag = 0;
#endif
      goto move_args_above_contB;
     move_args_above_contB_return_0:
      arg0K0 = stack_arg_count_1282X;
      goto L66427;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_34:
#else
    case 34 : 
#endif
      {
      stack_arg_count_1283X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 3))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 4)));
      return_pointer_offset_1284X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2)));
      if ((0 == return_pointer_offset_1284X)) {
        merged_arg0K0 = stack_arg_count_1283X;
#ifdef USE_DIRECT_THREADING
        move_args_above_contB_return_address = &&move_args_above_contB_return_1;
#else
        move_args_above_contB_return_tag = 1;
#endif
        goto move_args_above_contB;
       move_args_above_contB_return_1:
        goto L33599;}
      else {
        code_pointer_1285X = (Scode_pointerS) + return_pointer_offset_1284X;
        ScontS = ((SstackS) + (PS_SHIFT_LEFT_INLINE(stack_arg_count_1283X, 3)));
        *((long *) (ScontS)) = (long) ((((long) code_pointer_1285X)));
        goto L33599;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_35:
#else
    case 35 : 
#endif
      {
      v_1286X = *((unsigned char *) ((Scode_pointerS) + 4));
      if ((0 == v_1286X)) {
        arg0K0 = 2;
        goto L67357;}
      else {
        arg0K0 = 4;
        goto L67357;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_36:
#else
    case 36 : 
#endif
      {
      v_1287X = *((unsigned char *) ((Scode_pointerS) + 4));
      if ((0 == v_1287X)) {
        arg0K0 = 2;
        goto L32751;}
      else {
        arg0K0 = 4;
        goto L32751;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_37:
#else
    case 37 : 
#endif
      {
      v_1288X = *((unsigned char *) ((Scode_pointerS) + 5));
      if ((0 == v_1288X)) {
        arg0K0 = 2;
        goto L32703;}
      else {
        arg0K0 = 4;
        goto L32703;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_38:
#else
    case 38 : 
#endif
      {
      v_1289X = (s48_Sstack_limitS) == (((char *) -1));
      if (v_1289X) {
#ifdef USE_DIRECT_THREADING
        pending_interruptP_return_address = &&pending_interruptP_return_3;
#else
        pending_interruptP_return_tag = 3;
#endif
        goto pending_interruptP;
       pending_interruptP_return_3:
        v_1290X = pending_interruptP0_return_value;
        if (v_1290X) {
          goto L32995;}
        else {
          goto L67370;}}
      else {
        goto L67370;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_39:
#else
    case 39 : 
#endif
      {
      list_args_1291X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      stack_nargs_1292X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 3))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 4)));
      merged_arg0K0 = list_args_1291X;
#ifdef USE_DIRECT_THREADING
      okay_argument_list_return_address = &&okay_argument_list_return_0;
#else
      okay_argument_list_return_tag = 0;
#endif
      goto okay_argument_list;
     okay_argument_list_return_0:
      okayP_1293X = okay_argument_list0_return_value;
      length_1294X = okay_argument_list1_return_value;
      if (okayP_1293X) {
        return_pointer_offset_1295X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2)));
        if ((0 == return_pointer_offset_1295X)) {
          merged_arg0K0 = stack_nargs_1292X;
#ifdef USE_DIRECT_THREADING
          move_args_above_contB_return_address = &&move_args_above_contB_return_2;
#else
          move_args_above_contB_return_tag = 2;
#endif
          goto move_args_above_contB;
         move_args_above_contB_return_2:
          arg0K0 = stack_nargs_1292X;
          arg0K1 = list_args_1291X;
          arg0K2 = length_1294X;
          goto L65449;}
        else {
          code_pointer_1296X = (Scode_pointerS) + return_pointer_offset_1295X;
          ScontS = ((SstackS) + (PS_SHIFT_LEFT_INLINE(stack_nargs_1292X, 3)));
          *((long *) (ScontS)) = (long) ((((long) code_pointer_1296X)));
          arg0K0 = stack_nargs_1292X;
          arg0K1 = list_args_1291X;
          arg0K2 = length_1294X;
          goto L65449;}}
      else {
        merged_arg0K0 = list_args_1291X;
        merged_arg0K1 = stack_nargs_1292X;
#ifdef USE_DIRECT_THREADING
        pop_args_GlistSAgc_return_address = &&pop_args_GlistSAgc_return_1;
#else
        pop_args_GlistSAgc_return_tag = 1;
#endif
        goto pop_args_GlistSAgc;
       pop_args_GlistSAgc_return_1:
        args_1297X = pop_args_GlistSAgc0_return_value;push_exception_setupB(5, 0);
        x_1298X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1298X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (args_1297X);
        arg0K0 = 2;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_40:
#else
    case 40 : 
#endif
      {
      SstackS = ((SstackS) + 8);
      p_1299X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      stack_nargs_1300X = PS_SHIFT_RIGHT_INLINE(p_1299X, 2);
      SvalS = (*((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE(stack_nargs_1300X, 3)))));
      merged_arg0K0 = stack_nargs_1300X;
#ifdef USE_DIRECT_THREADING
      move_args_above_contB_return_address = &&move_args_above_contB_return_3;
#else
      move_args_above_contB_return_tag = 3;
#endif
      goto move_args_above_contB;
     move_args_above_contB_return_3:
      rest_list_1301X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((25 == rest_list_1301X)) {
        v_1302X = *((long *) (SstackS));
        SstackS = ((SstackS) + 8);
        arg0K0 = v_1302X;
        arg0K1 = (-2 + stack_nargs_1300X);
        goto L23642;}
      else {
        if ((25 == (*((long *) ((((char *) (-3 + rest_list_1301X))) + 8))))) {
          arg0K0 = (*((long *) (((char *) (-3 + rest_list_1301X)))));
          arg0K1 = (-1 + stack_nargs_1300X);
          goto L23642;}
        else {
          arg0K0 = (*((long *) ((((char *) (-3 + (*((long *) ((((char *) (-3 + rest_list_1301X))) + 8)))))) + 8)));
          arg0K1 = rest_list_1301X;
          goto L23687;}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_41:
#else
    case 41 : 
#endif
      {
      cont_1303X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((3 == (3 & cont_1303X))) {
        if ((10 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + cont_1303X))))), 2))))) {
          merged_arg0K0 = cont_1303X;
          merged_arg0K1 = 0;
#ifdef USE_DIRECT_THREADING
          copy_continuation_from_heapB_return_address = &&copy_continuation_from_heapB_return_0;
#else
          copy_continuation_from_heapB_return_tag = 0;
#endif
          goto copy_continuation_from_heapB;
         copy_continuation_from_heapB_return_0:
          goto L33557;}
        else {
          goto L33566;}}
      else {
        goto L33566;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_42:
#else
    case 42 : 
#endif
      {
      goto L66038;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_43:
#else
    case 43 : 
#endif
      {
      arg0K0 = ((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2))));
      arg0K1 = 25;
      arg0K2 = 0;
      goto L33224;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_44:
#else
    case 44 : 
#endif
      {
      p_1304X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      p_1305X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      stack_nargs_1306X = PS_SHIFT_RIGHT_INLINE(p_1305X, 2);
      rest_list_1307X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg0K0 = stack_nargs_1306X;
      arg0K1 = rest_list_1307X;
      arg0K2 = ((PS_SHIFT_RIGHT_INLINE(p_1304X, 2)) - stack_nargs_1306X);
      goto L33224;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_46:
#else
    case 46 : 
#endif
      {
      template_1308X = *((long *) ((((char *) (-3 + (*((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 3))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 4)))), 3)))))))) + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 5))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 6)))), 3))));
      code_1309X = *((long *) (((char *) (-3 + template_1308X))));
      nargs_1310X = *((unsigned char *) ((Scode_pointerS) + 7));
      return_pointer_offset_1311X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2)));
      if ((0 == return_pointer_offset_1311X)) {
        merged_arg0K0 = nargs_1310X;
#ifdef USE_DIRECT_THREADING
        move_args_above_contB_return_address = &&move_args_above_contB_return_4;
#else
        move_args_above_contB_return_tag = 4;
#endif
        goto move_args_above_contB;
       move_args_above_contB_return_4:
        goto L37880;}
      else {
        code_pointer_1312X = (Scode_pointerS) + return_pointer_offset_1311X;
        ScontS = ((SstackS) + (PS_SHIFT_LEFT_INLINE(nargs_1310X, 3)));
        *((long *) (ScontS)) = (long) ((((long) code_pointer_1312X)));
        goto L37880;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_47:
#else
    case 47 : 
#endif
      {
      if ((1 == (SvalS))) {
        Scode_pointerS = ((Scode_pointerS) + ((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2)))));
        arg3K0 = (Scode_pointerS);
        goto L36237;}
      else {
        Scode_pointerS = ((Scode_pointerS) + 3);
        arg3K0 = (Scode_pointerS);
        goto L36237;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_48:
#else
    case 48 : 
#endif
      {
      Scode_pointerS = ((Scode_pointerS) + 3);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_49:
#else
    case 49 : 
#endif
      {
      Scode_pointerS = ((Scode_pointerS) + ((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2)))));
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_50:
#else
    case 50 : 
#endif
      {
      Scode_pointerS = ((Scode_pointerS) + (0 - ((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2))))));
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_51:
#else
    case 51 : 
#endif
      {
      if ((0 == (3 & (SvalS)))) {
        p_1313X = SvalS;
        max_1314X = *((unsigned char *) ((Scode_pointerS) + 1));
        val_1315X = PS_SHIFT_RIGHT_INLINE(p_1313X, 2);
        if ((val_1315X < 0)) {
          goto L36556;}
        else {
          if ((val_1315X < max_1314X)) {
            index_1316X = 1 + (PS_SHIFT_LEFT_INLINE(val_1315X, 1));
            arg0K0 = ((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + (1 + index_1316X)))), 8)) + (*((unsigned char *) ((Scode_pointerS) + (2 + index_1316X)))));
            goto L36558;}
          else {
            goto L36556;}}}
      else {push_exception_setupB(5, 0);
        x_1317X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1317X);
        arg0K0 = 1;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_52:
#else
    case 52 : 
#endif
      {
      stack_nargs_1318X = PS_SHIFT_RIGHT_INLINE((*((long *) (SstackS))), 2);
      if ((0 == stack_nargs_1318X)) {
        rest_list_1319X = *((long *) ((SstackS) + 8));
        arg0_1320X = *((long *) ((SstackS) + 16));
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg0_1320X);
        SvalS = (*((long *) (((char *) (-3 + rest_list_1319X)))));
        goto L37145;}
      else {
        arg0_1321X = *((long *) ((SstackS) + (8 + (PS_SHIFT_LEFT_INLINE(stack_nargs_1318X, 3)))));
        arg1_1322X = *((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE(stack_nargs_1318X, 3))));
        *((long *) ((SstackS) + (8 + (PS_SHIFT_LEFT_INLINE(stack_nargs_1318X, 3))))) = (long) (1);
        *((long *) (SstackS)) = (long) ((-4 + (PS_SHIFT_LEFT_INLINE(stack_nargs_1318X, 2))));
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg0_1321X);
        SvalS = arg1_1322X;
        goto L37145;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_53:
#else
    case 53 : 
#endif
      {
      stack_nargs_1323X = PS_SHIFT_RIGHT_INLINE((*((long *) (SstackS))), 2);
      if ((stack_nargs_1323X == 0)) {
        rest_list_1324X = *((long *) ((SstackS) + 8));
        if ((25 == (*((long *) ((((char *) (-3 + rest_list_1324X))) + 8))))) {
          arg0K0 = 1;
          goto L36454;}
        else {
          *((long *) ((SstackS) + 8)) = (long) ((*((long *) ((((char *) (-3 + rest_list_1324X))) + 8))));
          *((long *) ((SstackS) + 16)) = (long) ((SvalS));
          arg0K0 = -2;
          goto L36454;}}
      else {
        if ((stack_nargs_1323X == 1)) {
          if ((25 == (*((long *) ((SstackS) + 8))))) {
            arg0K0 = 1;
            goto L36454;}
          else {
            *((long *) (SstackS)) = (long) (0);
            *((long *) ((SstackS) + 16)) = (long) ((SvalS));
            arg0K0 = -2;
            goto L36454;}}
        else {
          *((long *) ((SstackS) + (8 + (PS_SHIFT_LEFT_INLINE(stack_nargs_1323X, 3))))) = (long) ((SvalS));
          arg0K0 = -2;
          goto L36454;}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_54:
#else
    case 54 : 
#endif
      {
      if ((1 == (SvalS))) {
        Scode_pointerS = ((Scode_pointerS) + 1);
        arg3K0 = (Scode_pointerS);
        goto L36237;}
      else {
        x_1325X = PS_SHIFT_RIGHT_INLINE((*((long *) (SstackS))), 2);
        if ((x_1325X == 0)) {
          rest_list_1326X = *((long *) ((SstackS) + 8));
          if ((25 == (*((long *) ((((char *) (-3 + rest_list_1326X))) + 8))))) {
            arg0K0 = 1;
            goto L37036;}
          else {
            *((long *) ((SstackS) + 8)) = (long) ((*((long *) ((((char *) (-3 + rest_list_1326X))) + 8))));
            *((long *) ((SstackS) + 16)) = (long) ((*((long *) (((char *) (-3 + rest_list_1326X))))));
            arg0K0 = -2;
            goto L37036;}}
        else {
          if ((x_1325X == 1)) {
            if ((25 == (*((long *) ((SstackS) + 8))))) {
              arg0K0 = 1;
              goto L37036;}
            else {
              *((long *) (SstackS)) = (long) (0);
              arg0K0 = -2;
              goto L37036;}}
          else {
            arg0K0 = -2;
            goto L37036;}}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_55:
#else
    case 55 : 
#endif
      {
      arg2_1327X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      x_1328X = SvalS;
      if ((arg2_1327X == x_1328X)) {
        arg0K0 = 5;
        goto L67418;}
      else {
        arg0K0 = 1;
        goto L67418;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_56:
#else
    case 56 : 
#endif
      {
      x_1329X = SvalS;
      if ((0 == (3 & x_1329X))) {
        arg0K0 = 5;
        goto L67430;}
      else {
        if ((3 == (3 & x_1329X))) {
          if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + x_1329X))))), 2))))) {
            arg0K0 = 5;
            goto L67430;}
          else {
            goto L21059;}}
        else {
          goto L21059;}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_57:
#else
    case 57 : 
#endif
      {
      n_1330X = SvalS;
      if ((0 == (3 & n_1330X))) {
        goto L56372;}
      else {
        if ((3 == (3 & n_1330X))) {
          if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + n_1330X))))), 2))))) {
            goto L56372;}
          else {
            goto L56373;}}
        else {
          goto L56373;}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_58:
#else
    case 58 : 
#endif
      {
      n_1331X = SvalS;
      if ((0 == (3 & n_1331X))) {
        goto L56529;}
      else {
        if ((3 == (3 & n_1331X))) {
          if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + n_1331X))))), 2))))) {
            goto L56529;}
          else {
            goto L56522;}}
        else {
          goto L56522;}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_59:
#else
    case 59 : 
#endif
      {
      arg0K0 = (SvalS);
      goto L56732;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_60:
#else
    case 60 : 
#endif
      {
      arg0K0 = (SvalS);
      goto L56732;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_61:
#else
    case 61 : 
#endif
      {
      n_1332X = SvalS;
      if ((0 == (3 & n_1332X))) {
        goto L47869;}
      else {
        if ((3 == (3 & n_1332X))) {
          if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + n_1332X))))), 2))))) {
            goto L47869;}
          else {
            goto L47870;}}
        else {
          goto L47870;}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_62:
#else
    case 62 : 
#endif
      {
      x_1333X = SvalS;push_exception_setupB(5, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1333X);
      arg0K0 = 1;
      goto L33796;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_63:
#else
    case 63 : 
#endif
      {
      x_1334X = SvalS;push_exception_setupB(5, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1334X);
      arg0K0 = 1;
      goto L33796;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_64:
#else
    case 64 : 
#endif
      {
      arg2_1335X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      y_1336X = SvalS;
      if ((0 == (3 & (arg2_1335X | y_1336X)))) {s48_make_availableAgc(24);
        x_1337X = (PS_SHIFT_RIGHT_INLINE(arg2_1335X, 2)) + (PS_SHIFT_RIGHT_INLINE(y_1336X, 2));
        if ((2305843009213693951 < x_1337X)) {
          goto L47995;}
        else {
          if ((x_1337X < -2305843009213693952)) {
            goto L47995;}
          else {
            arg0K0 = (PS_SHIFT_LEFT_INLINE(x_1337X, 2));
            goto L47941;}}}
      else {
        if ((0 == (3 & arg2_1335X))) {
          goto L47947;}
        else {
          if ((3 == (3 & arg2_1335X))) {
            if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1335X))))), 2))))) {
              goto L47947;}
            else {
              goto L47956;}}
          else {
            goto L47956;}}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_65:
#else
    case 65 : 
#endif
      {
      arg2_1338X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      y_1339X = SvalS;
      if ((0 == (3 & (arg2_1338X | y_1339X)))) {
        a_1340X = PS_SHIFT_RIGHT_INLINE(arg2_1338X, 2);
        b_1341X = PS_SHIFT_RIGHT_INLINE(y_1339X, 2);
        if ((a_1340X < 0)) {
          arg0K0 = (0 - a_1340X);
          goto L12468;}
        else {
          arg0K0 = a_1340X;
          goto L12468;}}
      else {
        if ((0 == (3 & arg2_1338X))) {
          goto L58516;}
        else {
          if ((3 == (3 & arg2_1338X))) {
            if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1338X))))), 2))))) {
              goto L58516;}
            else {
              goto L58525;}}
          else {
            goto L58525;}}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_66:
#else
    case 66 : 
#endif
      {
      arg2_1342X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      y_1343X = SvalS;
      if ((0 == (3 & (arg2_1342X | y_1343X)))) {s48_make_availableAgc(24);
        x_1344X = (PS_SHIFT_RIGHT_INLINE(arg2_1342X, 2)) - (PS_SHIFT_RIGHT_INLINE(y_1343X, 2));
        if ((2305843009213693951 < x_1344X)) {
          goto L48284;}
        else {
          if ((x_1344X < -2305843009213693952)) {
            goto L48284;}
          else {
            arg0K0 = (PS_SHIFT_LEFT_INLINE(x_1344X, 2));
            goto L48230;}}}
      else {
        if ((0 == (3 & arg2_1342X))) {
          goto L48236;}
        else {
          if ((3 == (3 & arg2_1342X))) {
            if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1342X))))), 2))))) {
              goto L48236;}
            else {
              goto L48245;}}
          else {
            goto L48245;}}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_67:
#else
    case 67 : 
#endif
      {
      arg2_1345X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      y_1346X = SvalS;
      if ((0 == y_1346X)) {push_exception_setupB(5, 1);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg2_1345X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (y_1346X);
        arg0K0 = 2;
        goto L33796;}
      else {
        if ((0 == (3 & (arg2_1345X | y_1346X)))) {
          if ((0 == y_1346X)) {push_exception_setupB(5, 1);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (arg2_1345X);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (y_1346X);
            arg0K0 = 2;
            goto L33796;}
          else {
            a_1347X = PS_SHIFT_RIGHT_INLINE(arg2_1345X, 2);
            b_1348X = PS_SHIFT_RIGHT_INLINE(y_1346X, 2);
            if ((a_1347X < 0)) {
              arg0K0 = (0 - a_1347X);
              goto L12726;}
            else {
              arg0K0 = a_1347X;
              goto L12726;}}}
        else {
          if ((0 == (3 & arg2_1345X))) {
            goto L58769;}
          else {
            if ((3 == (3 & arg2_1345X))) {
              if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1345X))))), 2))))) {
                goto L58769;}
              else {
                goto L58806;}}
            else {
              goto L58806;}}}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_68:
#else
    case 68 : 
#endif
      {
      arg2_1349X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      y_1350X = SvalS;
      if ((0 == (3 & (arg2_1349X | y_1350X)))) {
        if ((arg2_1349X == y_1350X)) {
          arg0K0 = 5;
          goto L48515;}
        else {
          arg0K0 = 1;
          goto L48515;}}
      else {
        if ((0 == (3 & arg2_1349X))) {
          goto L48521;}
        else {
          if ((3 == (3 & arg2_1349X))) {
            if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1349X))))), 2))))) {
              goto L48521;}
            else {
              goto L48532;}}
          else {
            goto L48532;}}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_69:
#else
    case 69 : 
#endif
      {
      arg2_1351X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      y_1352X = SvalS;
      if ((0 == (3 & (arg2_1351X | y_1352X)))) {
        if ((arg2_1351X < y_1352X)) {
          arg0K0 = 5;
          goto L48775;}
        else {
          arg0K0 = 1;
          goto L48775;}}
      else {
        if ((0 == (3 & arg2_1351X))) {
          goto L48781;}
        else {
          if ((3 == (3 & arg2_1351X))) {
            if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1351X))))), 2))))) {
              goto L48781;}
            else {
              goto L48792;}}
          else {
            goto L48792;}}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_70:
#else
    case 70 : 
#endif
      {
      arg2_1353X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      y_1354X = SvalS;
      if ((0 == (3 & (arg2_1353X | y_1354X)))) {
        if ((y_1354X < arg2_1353X)) {
          arg0K0 = 5;
          goto L49098;}
        else {
          arg0K0 = 1;
          goto L49098;}}
      else {
        if ((0 == (3 & arg2_1353X))) {
          goto L49104;}
        else {
          if ((3 == (3 & arg2_1353X))) {
            if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1353X))))), 2))))) {
              goto L49104;}
            else {
              goto L49115;}}
          else {
            goto L49115;}}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_71:
#else
    case 71 : 
#endif
      {
      arg2_1355X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      y_1356X = SvalS;
      if ((0 == (3 & (arg2_1355X | y_1356X)))) {
        if ((y_1356X < arg2_1355X)) {
          arg0K0 = 1;
          goto L49421;}
        else {
          arg0K0 = 5;
          goto L49421;}}
      else {
        if ((0 == (3 & arg2_1355X))) {
          goto L49427;}
        else {
          if ((3 == (3 & arg2_1355X))) {
            if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1355X))))), 2))))) {
              goto L49427;}
            else {
              goto L49438;}}
          else {
            goto L49438;}}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_72:
#else
    case 72 : 
#endif
      {
      arg2_1357X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      y_1358X = SvalS;
      if ((0 == (3 & (arg2_1357X | y_1358X)))) {
        if ((arg2_1357X < y_1358X)) {
          arg0K0 = 1;
          goto L49715;}
        else {
          arg0K0 = 5;
          goto L49715;}}
      else {
        if ((0 == (3 & arg2_1357X))) {
          goto L49721;}
        else {
          if ((3 == (3 & arg2_1357X))) {
            if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1357X))))), 2))))) {
              goto L49721;}
            else {
              goto L49732;}}
          else {
            goto L49732;}}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_73:
#else
    case 73 : 
#endif
      {
      arg2_1359X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      y_1360X = SvalS;
      if ((0 == y_1360X)) {push_exception_setupB(5, 1);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg2_1359X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (y_1360X);
        arg0K0 = 2;
        goto L33796;}
      else {
        if ((0 == (3 & (arg2_1359X | y_1360X)))) {
          if ((0 == y_1360X)) {
            val_1361X = Hinteger_op8731(arg2_1359X, y_1360X);
            SvalS = val_1361X;
            Scode_pointerS = ((Scode_pointerS) + 1);
            arg3K0 = (Scode_pointerS);
            goto L36237;}
          else {
            a_1362X = PS_SHIFT_RIGHT_INLINE(arg2_1359X, 2);
            b_1363X = PS_SHIFT_RIGHT_INLINE(y_1360X, 2);
            if ((a_1362X < 0)) {
              arg0K0 = (0 - a_1362X);
              goto L13141;}
            else {
              arg0K0 = a_1362X;
              goto L13141;}}}
        else {
          if ((0 == (3 & arg2_1359X))) {
            goto L50021;}
          else {
            if ((3 == (3 & arg2_1359X))) {
              if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1359X))))), 2))))) {
                goto L50021;}
              else {
                goto L50030;}}
            else {
              goto L50030;}}}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_74:
#else
    case 74 : 
#endif
      {
      arg2_1364X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      y_1365X = SvalS;
      if ((0 == y_1365X)) {push_exception_setupB(5, 1);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg2_1364X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (y_1365X);
        arg0K0 = 2;
        goto L33796;}
      else {
        if ((0 == (3 & (arg2_1364X | y_1365X)))) {
          if ((0 == y_1365X)) {
            val_1366X = Hinteger_op8662(arg2_1364X, y_1365X);
            SvalS = val_1366X;
            Scode_pointerS = ((Scode_pointerS) + 1);
            arg3K0 = (Scode_pointerS);
            goto L36237;}
          else {
            a_1367X = PS_SHIFT_RIGHT_INLINE(arg2_1364X, 2);
            if ((a_1367X < 0)) {
              arg0K0 = (0 - a_1367X);
              goto L50235;}
            else {
              arg0K0 = a_1367X;
              goto L50235;}}}
        else {
          if ((0 == (3 & arg2_1364X))) {
            goto L50197;}
          else {
            if ((3 == (3 & arg2_1364X))) {
              if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1364X))))), 2))))) {
                goto L50197;}
              else {
                goto L50206;}}
            else {
              goto L50206;}}}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_75:
#else
    case 75 : 
#endif
      {
      n_1368X = SvalS;
      if ((0 == (3 & n_1368X))) {
        goto L50384;}
      else {
        if ((3 == (3 & n_1368X))) {
          if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + n_1368X))))), 2))))) {
            goto L50384;}
          else {
            goto L50385;}}
        else {
          goto L50385;}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_76:
#else
    case 76 : 
#endif
      {
      n_1369X = SvalS;
      if ((0 == (3 & n_1369X))) {
        goto L50439;}
      else {
        if ((3 == (3 & n_1369X))) {
          if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + n_1369X))))), 2))))) {
            goto L50439;}
          else {
            goto L50440;}}
        else {
          goto L50440;}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_77:
#else
    case 77 : 
#endif
      {
      n_1370X = SvalS;
      if ((0 == (3 & n_1370X))) {
        goto L50494;}
      else {
        if ((3 == (3 & n_1370X))) {
          if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + n_1370X))))), 2))))) {
            goto L50494;}
          else {
            goto L50497;}}
        else {
          goto L50497;}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_78:
#else
    case 78 : 
#endif
      {
      n_1371X = SvalS;
      if ((0 == (3 & n_1371X))) {
        goto L50554;}
      else {
        if ((3 == (3 & n_1371X))) {
          if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + n_1371X))))), 2))))) {
            goto L50554;}
          else {
            goto L50555;}}
        else {
          goto L50555;}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_79:
#else
    case 79 : 
#endif
      {
      n_1372X = SvalS;
      if ((0 == (3 & n_1372X))) {
        goto L50609;}
      else {
        if ((3 == (3 & n_1372X))) {
          if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + n_1372X))))), 2))))) {
            goto L50609;}
          else {
            goto L50612;}}
        else {
          goto L50612;}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_80:
#else
    case 80 : 
#endif
      {
      x_1373X = SvalS;push_exception_setupB(5, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1373X);
      arg0K0 = 1;
      goto L33796;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_81:
#else
    case 81 : 
#endif
      {
      x_1374X = SvalS;push_exception_setupB(5, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1374X);
      arg0K0 = 1;
      goto L33796;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_82:
#else
    case 82 : 
#endif
      {
      x_1375X = SvalS;push_exception_setupB(5, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1375X);
      arg0K0 = 1;
      goto L33796;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_83:
#else
    case 83 : 
#endif
      {
      x_1376X = SvalS;push_exception_setupB(5, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1376X);
      arg0K0 = 1;
      goto L33796;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_84:
#else
    case 84 : 
#endif
      {
      x_1377X = SvalS;push_exception_setupB(5, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1377X);
      arg0K0 = 1;
      goto L33796;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_85:
#else
    case 85 : 
#endif
      {
      x_1378X = SvalS;push_exception_setupB(5, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1378X);
      arg0K0 = 1;
      goto L33796;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_86:
#else
    case 86 : 
#endif
      {
      x_1379X = SvalS;push_exception_setupB(5, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1379X);
      arg0K0 = 1;
      goto L33796;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_87:
#else
    case 87 : 
#endif
      {
      x_1380X = SvalS;push_exception_setupB(5, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1380X);
      arg0K0 = 1;
      goto L33796;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_88:
#else
    case 88 : 
#endif
      {
      x_1381X = SvalS;
      if ((0 == (3 & x_1381X))) {
        goto L60096;}
      else {
        if ((3 == (3 & x_1381X))) {
          if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + x_1381X))))), 2))))) {
            goto L60096;}
          else {
            goto L60099;}}
        else {
          goto L60099;}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_89:
#else
    case 89 : 
#endif
      {
      x_1382X = SvalS;
      if ((0 == (3 & x_1382X))) {
        goto L63554;}
      else {
        if ((3 == (3 & x_1382X))) {
          if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + x_1382X))))), 2))))) {
            goto L63554;}
          else {
            goto L63557;}}
        else {
          goto L63557;}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_90:
#else
    case 90 : 
#endif
      {
      x_1383X = SvalS;push_exception_setupB(5, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1383X);
      arg0K0 = 1;
      goto L33796;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_91:
#else
    case 91 : 
#endif
      {
      arg2_1384X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      x_1385X = SvalS;push_exception_setupB(5, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (arg2_1384X);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1385X);
      arg0K0 = 2;
      goto L33796;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_92:
#else
    case 92 : 
#endif
      {
      arg2_1386X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      x_1387X = SvalS;push_exception_setupB(5, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (arg2_1386X);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1387X);
      arg0K0 = 2;
      goto L33796;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_93:
#else
    case 93 : 
#endif
      {
      arg2_1388X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      x_1389X = SvalS;push_exception_setupB(5, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (arg2_1388X);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1389X);
      arg0K0 = 2;
      goto L33796;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_94:
#else
    case 94 : 
#endif
      {
      x_1390X = SvalS;
      if ((0 == (3 & x_1390X))) {
        SvalS = (~ (3 | x_1390X));
        Scode_pointerS = ((Scode_pointerS) + 1);
        arg3K0 = (Scode_pointerS);
        goto L36237;}
      else {
        if ((0 == (3 & x_1390X))) {
          goto L50755;}
        else {
          if ((3 == (3 & x_1390X))) {
            if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + x_1390X))))), 2))))) {
              goto L50755;}
            else {
              goto L50758;}}
          else {
            goto L50758;}}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_95:
#else
    case 95 : 
#endif
      {
      x_1391X = SvalS;
      if ((0 == (3 & x_1391X))) {
        x_1392X = PS_SHIFT_RIGHT_INLINE(x_1391X, 2);
        if ((x_1392X < 0)) {
          arg0K0 = (~ x_1392X);
          goto L50846;}
        else {
          arg0K0 = x_1392X;
          goto L50846;}}
      else {
        if ((0 == (3 & x_1391X))) {
          goto L50829;}
        else {
          if ((3 == (3 & x_1391X))) {
            if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + x_1391X))))), 2))))) {
              goto L50829;}
            else {
              goto L50832;}}
          else {
            goto L50832;}}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_96:
#else
    case 96 : 
#endif
      {
      arg2_1393X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      y_1394X = SvalS;
      if ((0 == (3 & (arg2_1393X | y_1394X)))) {
        SvalS = (arg2_1393X & y_1394X);
        Scode_pointerS = ((Scode_pointerS) + 1);
        arg3K0 = (Scode_pointerS);
        goto L36237;}
      else {
        if ((0 == (3 & arg2_1393X))) {
          goto L50931;}
        else {
          if ((3 == (3 & arg2_1393X))) {
            if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1393X))))), 2))))) {
              goto L50931;}
            else {
              goto L50940;}}
          else {
            goto L50940;}}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_97:
#else
    case 97 : 
#endif
      {
      arg2_1395X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      y_1396X = SvalS;
      if ((0 == (3 & (arg2_1395X | y_1396X)))) {
        SvalS = (arg2_1395X | y_1396X);
        Scode_pointerS = ((Scode_pointerS) + 1);
        arg3K0 = (Scode_pointerS);
        goto L36237;}
      else {
        if ((0 == (3 & arg2_1395X))) {
          goto L51094;}
        else {
          if ((3 == (3 & arg2_1395X))) {
            if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1395X))))), 2))))) {
              goto L51094;}
            else {
              goto L51103;}}
          else {
            goto L51103;}}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_98:
#else
    case 98 : 
#endif
      {
      arg2_1397X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      y_1398X = SvalS;
      if ((0 == (3 & (arg2_1397X | y_1398X)))) {
        SvalS = (arg2_1397X ^ y_1398X);
        Scode_pointerS = ((Scode_pointerS) + 1);
        arg3K0 = (Scode_pointerS);
        goto L36237;}
      else {
        if ((0 == (3 & arg2_1397X))) {
          goto L51257;}
        else {
          if ((3 == (3 & arg2_1397X))) {
            if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1397X))))), 2))))) {
              goto L51257;}
            else {
              goto L51266;}}
          else {
            goto L51266;}}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_99:
#else
    case 99 : 
#endif
      {
      arg2_1399X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      y_1400X = SvalS;
      if ((3 == (3 & y_1400X))) {
        if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1400X))))), 2))))) {
          v_1401X = s48_bignum_test((((char *) (-3 + y_1400X))));
          if ((1 == v_1401X)) {push_exception_setupB(7, 1);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (arg2_1399X);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (y_1400X);
            arg0K0 = 2;
            goto L33796;}
          else {
            if ((0 == (3 & arg2_1399X))) {
              if ((arg2_1399X < 0)) {
                arg0K0 = -4;
                goto L47649;}
              else {
                arg0K0 = 0;
                goto L47649;}}
            else {
              if ((3 == (3 & arg2_1399X))) {
                if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1399X))))), 2))))) {
                  v_1402X = s48_bignum_test((((char *) (-3 + arg2_1399X))));
                  if ((1 == v_1402X)) {
                    arg0K0 = 0;
                    goto L47665;}
                  else {
                    arg0K0 = -4;
                    goto L47665;}}
                else {
                  goto L47666;}}
              else {
                goto L47666;}}}}
        else {
          goto L59156;}}
      else {
        goto L59156;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_100:
#else
    case 100 : 
#endif
      {
      x_1403X = SvalS;
      if ((9 == (255 & x_1403X))) {
        arg0K0 = 5;
        goto L67689;}
      else {
        arg0K0 = 1;
        goto L67689;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_101:
#else
    case 101 : 
#endif
      {
      arg2_1404X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((9 == (255 & arg2_1404X))) {
        if ((9 == (255 & (SvalS)))) {
          x_1405X = SvalS;
          if ((arg2_1404X == x_1405X)) {
            arg0K0 = 5;
            goto L56173;}
          else {
            arg0K0 = 1;
            goto L56173;}}
        else {
          goto L56144;}}
      else {
        goto L56144;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_102:
#else
    case 102 : 
#endif
      {
      arg2_1406X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((9 == (255 & arg2_1406X))) {
        if ((9 == (255 & (SvalS)))) {
          x_1407X = SvalS;
          if ((arg2_1406X < x_1407X)) {
            arg0K0 = 5;
            goto L56081;}
          else {
            arg0K0 = 1;
            goto L56081;}}
        else {
          goto L56052;}}
      else {
        goto L56052;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_103:
#else
    case 103 : 
#endif
      {
      if ((9 == (255 & (SvalS)))) {
        SvalS = (-4 & (PS_SHIFT_RIGHT_INLINE((SvalS), 6)));
        Scode_pointerS = ((Scode_pointerS) + 1);
        arg3K0 = (Scode_pointerS);
        goto L36237;}
      else {push_exception_setupB(5, 1);
        x_1408X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1408X);
        arg0K0 = 1;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_104:
#else
    case 104 : 
#endif
      {
      if ((0 == (3 & (SvalS)))) {
        x_1409X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
        if ((x_1409X < 0)) {
          goto L60405;}
        else {
          if ((55295 < x_1409X)) {
            if ((x_1409X < 57344)) {
              goto L60405;}
            else {
              if ((1114111 < x_1409X)) {
                goto L60405;}
              else {
                goto L60411;}}}
          else {
            goto L60411;}}}
      else {push_exception_setupB(5, 1);
        x_1410X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1410X);
        arg0K0 = 1;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_105:
#else
    case 105 : 
#endif
      {
      if ((0 == (3 & (SvalS)))) {
        x_1411X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
        if ((x_1411X < 0)) {
          arg0K0 = 1;
          goto L55979;}
        else {
          if ((55295 < x_1411X)) {
            if ((x_1411X < 57344)) {
              arg0K0 = 1;
              goto L55979;}
            else {
              if ((1114111 < x_1411X)) {
                arg0K0 = 1;
                goto L55979;}
              else {
                arg0K0 = 5;
                goto L55979;}}}
          else {
            arg0K0 = 5;
            goto L55979;}}}
      else {push_exception_setupB(5, 1);
        x_1412X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1412X);
        arg0K0 = 1;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_106:
#else
    case 106 : 
#endif
      {
      x_1413X = SvalS;
      if ((21 == x_1413X)) {
        arg0K0 = 5;
        goto L67722;}
      else {
        arg0K0 = 1;
        goto L67722;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_107:
#else
    case 107 : 
#endif
      {
      x_1414X = SvalS;
      type_1415X = *((unsigned char *) ((Scode_pointerS) + 1));
      if ((3 == (3 & x_1414X))) {
        if (((31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + x_1414X))))), 2))) == type_1415X)) {
          arg0K0 = 5;
          goto L67736;}
        else {
          arg0K0 = 1;
          goto L67736;}}
      else {
        arg0K0 = 1;
        goto L67736;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_108:
#else
    case 108 : 
#endif
      {
      stob_1416X = SvalS;
      type_1417X = *((unsigned char *) ((Scode_pointerS) + 1));
      if ((3 == (3 & stob_1416X))) {
        if (((31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + stob_1416X))))), 2))) == type_1417X)) {
          SvalS = (-4 & (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + stob_1416X))))), 8))), 1)));
          Scode_pointerS = ((Scode_pointerS) + 2);
          arg3K0 = (Scode_pointerS);
          goto L36237;}
        else {
          goto L39018;}}
      else {
        goto L39018;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_109:
#else
    case 109 : 
#endif
      {
      len_1418X = *((unsigned char *) ((Scode_pointerS) + 1));s48_make_availableAgc((8 + (PS_SHIFT_LEFT_INLINE(len_1418X, 3))));
      type_1419X = *((unsigned char *) ((Scode_pointerS) + 2));
      len_1420X = PS_SHIFT_LEFT_INLINE(len_1418X, 3);
      addr_1421X = s48_allocate_small((8 + len_1420X));
      *((long *) addr_1421X) = (long) ((2 + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE(len_1420X, 6)) + type_1419X), 2))));
      new_1422X = 3 + (((long) (addr_1421X + 8)));
      if ((len_1418X < 1)) {
        goto L39123;}
      else {
        *((long *) ((((char *) (-3 + new_1422X))) + (-8 + (PS_SHIFT_LEFT_INLINE(len_1418X, 3))))) = (long) ((SvalS));
        arg0K0 = (-2 + len_1418X);
        goto L39107;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_110:
#else
    case 110 : 
#endif
      {
      p_1423X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      len_1424X = PS_SHIFT_RIGHT_INLINE(p_1423X, 2);s48_make_availableAgc((8 + (PS_SHIFT_LEFT_INLINE(len_1424X, 3))));
      type_1425X = *((unsigned char *) ((Scode_pointerS) + 1));
      len_1426X = PS_SHIFT_LEFT_INLINE(len_1424X, 3);
      addr_1427X = s48_allocate_small((8 + len_1426X));
      *((long *) addr_1427X) = (long) ((2 + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE(len_1426X, 6)) + type_1425X), 2))));
      new_1428X = 3 + (((long) (addr_1427X + 8)));
      p_1429X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      stack_nargs_1430X = PS_SHIFT_RIGHT_INLINE(p_1429X, 2);
      rest_list_1431X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg0K0 = (-1 + stack_nargs_1430X);
      goto L39241;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_111:
#else
    case 111 : 
#endif
      {
      stob_1432X = SvalS;
      type_1433X = *((unsigned char *) ((Scode_pointerS) + 1));
      offset_1434X = *((unsigned char *) ((Scode_pointerS) + 2));
      if ((3 == (3 & stob_1432X))) {
        if (((31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + stob_1432X))))), 2))) == type_1433X)) {
          SvalS = (*((long *) ((((char *) (-3 + stob_1432X))) + (PS_SHIFT_LEFT_INLINE(offset_1434X, 3)))));
          Scode_pointerS = ((Scode_pointerS) + 3);
          arg3K0 = (Scode_pointerS);
          goto L36237;}
        else {
          goto L39409;}}
      else {
        goto L39409;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_112:
#else
    case 112 : 
#endif
      {
      arg2_1435X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      value_1436X = SvalS;
      type_1437X = *((unsigned char *) ((Scode_pointerS) + 1));
      offset_1438X = *((unsigned char *) ((Scode_pointerS) + 2));
      if ((3 == (3 & arg2_1435X))) {
        if (((31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1435X))))), 2))) == type_1437X)) {
          if ((3 == (3 & arg2_1435X))) {
            if ((0 == (128 & (*((long *) (((char *) (-11 + arg2_1435X)))))))) {
              v_1439X = *((unsigned char *) ((Scode_pointerS) + 3));
              if ((0 == v_1439X)) {
                goto L39551;}
              else {
                if ((1 == (*((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24))))) {
                  goto L39551;}
                else {
                  merged_arg0K0 = arg2_1435X;
                  merged_arg0K1 = (PS_SHIFT_LEFT_INLINE(offset_1438X, 2));
                  merged_arg0K2 = value_1436X;
#ifdef USE_DIRECT_THREADING
                  proposal_d_write_return_address = &&proposal_d_write_return_0;
#else
                  proposal_d_write_return_tag = 0;
#endif
                  goto proposal_d_write;
                 proposal_d_write_return_0:
                  goto L39560;}}}
            else {
              goto L39519;}}
          else {
            goto L39519;}}
        else {
          goto L39576;}}
      else {
        goto L39576;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_113:
#else
    case 113 : 
#endif
      {
      arg2_1440X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      init_1441X = SvalS;
      type_1442X = *((unsigned char *) ((Scode_pointerS) + 1));
      if ((0 == (3 & arg2_1440X))) {
        len_1443X = PS_SHIFT_RIGHT_INLINE(arg2_1440X, 2);
        if ((len_1443X < 0)) {
          goto L39777;}
        else {
          if ((9007199254740992 < len_1443X)) {
            goto L39777;}
          else {
            Stemp0S = init_1441X;
            len_in_bytes_1444X = PS_SHIFT_LEFT_INLINE(len_1443X, 3);
            addr_1445X = s48_allocate_tracedAgc((8 + len_in_bytes_1444X));
            if ((addr_1445X == NULL)) {
              arg0K0 = 1;
              goto L39794;}
            else {
              *((long *) addr_1445X) = (long) ((2 + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE(len_in_bytes_1444X, 6)) + type_1442X), 2))));
              arg0K0 = (3 + (((long) (addr_1445X + 8))));
              goto L39794;}}}}
      else {push_exception_setupB(5, 2);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(type_1442X, 2)));
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg2_1440X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (init_1441X);
        arg0K0 = 3;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_114:
#else
    case 114 : 
#endif
      {
      arg2_1446X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      index_1447X = SvalS;
      type_1448X = *((unsigned char *) ((Scode_pointerS) + 1));
      if ((0 == (3 & index_1447X))) {
        if ((3 == (3 & arg2_1446X))) {
          if (((31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1446X))))), 2))) == type_1448X)) {
            len_1449X = PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg2_1446X))))), 8))), 3);
            index_1450X = PS_SHIFT_RIGHT_INLINE(index_1447X, 2);
            if ((index_1450X < 0)) {
              goto L40067;}
            else {
              if ((index_1450X < len_1449X)) {
                v_1451X = *((unsigned char *) ((Scode_pointerS) + 2));
                if ((0 == v_1451X)) {
                  goto L40057;}
                else {
                  if ((1 == (*((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24))))) {
                    goto L40057;}
                  else {
                    merged_arg0K0 = arg2_1446X;
                    merged_arg0K1 = index_1447X;
#ifdef USE_DIRECT_THREADING
                    proposal_d_read_return_address = &&proposal_d_read_return_0;
#else
                    proposal_d_read_return_tag = 0;
#endif
                    goto proposal_d_read;
                   proposal_d_read_return_0:
                    v_1452X = proposal_d_read0_return_value;
                    arg0K0 = v_1452X;
                    goto L40066;}}}
              else {
                goto L40067;}}}
          else {
            goto L40022;}}
        else {
          goto L40022;}}
      else {
        goto L40022;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_115:
#else
    case 115 : 
#endif
      {
      arg2_1453X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg3_1454X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      value_1455X = SvalS;
      type_1456X = *((unsigned char *) ((Scode_pointerS) + 1));
      if ((0 == (3 & arg2_1453X))) {
        if ((3 == (3 & arg3_1454X))) {
          if (((31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg3_1454X))))), 2))) == type_1456X)) {
            if ((3 == (3 & arg3_1454X))) {
              if ((0 == (128 & (*((long *) (((char *) (-11 + arg3_1454X)))))))) {
                len_1457X = PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg3_1454X))))), 8))), 3);
                index_1458X = PS_SHIFT_RIGHT_INLINE(arg2_1453X, 2);
                if ((index_1458X < 0)) {
                  goto L40360;}
                else {
                  if ((index_1458X < len_1457X)) {
                    v_1459X = *((unsigned char *) ((Scode_pointerS) + 2));
                    if ((0 == v_1459X)) {
                      goto L40350;}
                    else {
                      if ((1 == (*((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24))))) {
                        goto L40350;}
                      else {
                        merged_arg0K0 = arg3_1454X;
                        merged_arg0K1 = arg2_1453X;
                        merged_arg0K2 = value_1455X;
#ifdef USE_DIRECT_THREADING
                        proposal_d_write_return_address = &&proposal_d_write_return_1;
#else
                        proposal_d_write_return_tag = 1;
#endif
                        goto proposal_d_write;
                       proposal_d_write_return_1:
                        goto L40359;}}}
                  else {
                    goto L40360;}}}
              else {
                goto L40313;}}
            else {
              goto L40313;}}
          else {
            goto L40297;}}
        else {
          goto L40297;}}
      else {
        goto L40297;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_116:
#else
    case 116 : 
#endif
      {
      addr_1460X = s48_allocate_untracedAgc(16);
      if ((addr_1460X == NULL)) {
        arg0K0 = 1;
        goto L67779;}
      else {
        *((long *) addr_1460X) = (long) (2122);
        arg0K0 = (3 + (((long) (addr_1460X + 8))));
        goto L67779;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_117:
#else
    case 117 : 
#endif
      {
      arg2_1461X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((0 == (3 & (arg2_1461X | (SvalS))))) {
        len_1462X = PS_SHIFT_RIGHT_INLINE(arg2_1461X, 2);
        init_1463X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
        if ((len_1462X < 0)) {
          goto L51553;}
        else {
          if ((9007199254740992 < (PS_SHIFT_RIGHT_INLINE((7 + len_1462X), 3)))) {
            goto L51553;}
          else {
            addr_1464X = s48_allocate_untracedAgc((8 + len_1462X));
            if ((addr_1464X == NULL)) {
              arg0K0 = 1;
              goto L51578;}
            else {
              *((long *) addr_1464X) = (long) ((70 + (PS_SHIFT_LEFT_INLINE(len_1462X, 8))));
              arg0K0 = (3 + (((long) (addr_1464X + 8))));
              goto L51578;}}}}
      else {push_exception_setupB(5, 1);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg2_1461X);
        x_1465X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1465X);
        arg0K0 = 2;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_118:
#else
    case 118 : 
#endif
      {
      obj_1466X = SvalS;
      if ((3 == (3 & obj_1466X))) {
        if ((17 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_1466X))))), 2))))) {
          SvalS = (PS_SHIFT_LEFT_INLINE((PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + (SvalS)))))), 8)), 2));
          Scode_pointerS = ((Scode_pointerS) + 1);
          arg3K0 = (Scode_pointerS);
          goto L36237;}
        else {
          goto L64829;}}
      else {
        goto L64829;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_119:
#else
    case 119 : 
#endif
      {
      arg2_1467X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((3 == (3 & arg2_1467X))) {
        if ((17 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1467X))))), 2))))) {
          if ((0 == (3 & (SvalS)))) {
            index_1468X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
            len_1469X = PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg2_1467X))))), 8);
            if ((index_1468X < 0)) {
              goto L60548;}
            else {
              if ((index_1468X < len_1469X)) {
                SvalS = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((((char *) (-3 + arg2_1467X))) + index_1468X))), 2));
                Scode_pointerS = ((Scode_pointerS) + 1);
                arg3K0 = (Scode_pointerS);
                goto L36237;}
              else {
                goto L60548;}}}
          else {
            goto L64235;}}
        else {
          goto L64235;}}
      else {
        goto L64235;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_120:
#else
    case 120 : 
#endif
      {
      arg2_1470X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg3_1471X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((3 == (3 & arg3_1471X))) {
        if ((17 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg3_1471X))))), 2))))) {
          if ((0 == (3 & (arg2_1470X | (SvalS))))) {
            index_1472X = PS_SHIFT_RIGHT_INLINE(arg2_1470X, 2);
            Kchar_1473X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
            if ((3 == (3 & arg3_1471X))) {
              if ((0 == (128 & (*((long *) (((char *) (-11 + arg3_1471X)))))))) {
                len_1474X = PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg3_1471X))))), 8);
                if ((index_1472X < 0)) {
                  goto L57752;}
                else {
                  if ((index_1472X < len_1474X)) {
                    *((unsigned char *) ((((char *) (-3 + arg3_1471X))) + index_1472X)) = (unsigned char) (Kchar_1473X);
                    SvalS = 13;
                    Scode_pointerS = ((Scode_pointerS) + 1);
                    arg3K0 = (Scode_pointerS);
                    goto L36237;}
                  else {
                    goto L57752;}}}
              else {
                goto L57731;}}
            else {
              goto L57731;}}
          else {
            goto L62895;}}
        else {
          goto L62895;}}
      else {
        goto L62895;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_121:
#else
    case 121 : 
#endif
      {
      arg2_1475X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((0 == (3 & (arg2_1475X | (SvalS))))) {
        len_1476X = PS_SHIFT_RIGHT_INLINE(arg2_1475X, 2);
        init_1477X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
        x_1478X = s48_gc_can_allocate_unmovableP();
        if (x_1478X) {
          if ((len_1476X < 0)) {
            goto L51764;}
          else {
            if ((9007199254740992 < (PS_SHIFT_RIGHT_INLINE((7 + len_1476X), 3)))) {
              goto L51764;}
            else {
              addr_1479X = s48_allocate_untraced_unmovableAgc((8 + len_1476X));
              if ((addr_1479X == NULL)) {
                arg0K0 = 1;
                goto L51789;}
              else {
                *((long *) addr_1479X) = (long) ((70 + (PS_SHIFT_LEFT_INLINE(len_1476X, 8))));
                arg0K0 = (3 + (((long) (addr_1479X + 8))));
                goto L51789;}}}}
        else {push_exception_setupB(15, 1);
          arg0K0 = 0;
          goto L33796;}}
      else {push_exception_setupB(5, 1);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg2_1475X);
        x_1480X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1480X);
        arg0K0 = 2;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_122:
#else
    case 122 : 
#endif
      {
      arg2_1481X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((0 == (3 & arg2_1481X))) {
        if ((9 == (255 & (SvalS)))) {
          len_1482X = PS_SHIFT_RIGHT_INLINE(arg2_1481X, 2);
          init_1483X = PS_SHIFT_RIGHT_INLINE((SvalS), 8);
          if ((len_1482X < 0)) {
            goto L51983;}
          else {
            if ((9007199254740992 < (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_LEFT_INLINE(len_1482X, 2))), 3)))) {
              goto L51983;}
            else {
              len_1484X = PS_SHIFT_LEFT_INLINE(len_1482X, 2);
              addr_1485X = s48_allocate_untracedAgc((8 + len_1484X));
              if ((addr_1485X == NULL)) {
                arg0K0 = 1;
                goto L52008;}
              else {
                *((long *) addr_1485X) = (long) ((66 + (PS_SHIFT_LEFT_INLINE(len_1484X, 8))));
                arg0K0 = (3 + (((long) (addr_1485X + 8))));
                goto L52008;}}}}
        else {
          goto L60704;}}
      else {
        goto L60704;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_123:
#else
    case 123 : 
#endif
      {
      obj_1486X = SvalS;
      if ((3 == (3 & obj_1486X))) {
        if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_1486X))))), 2))))) {
          x_1487X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + (SvalS)))))), 8)) / 4;
          SvalS = (PS_SHIFT_LEFT_INLINE(x_1487X, 2));
          Scode_pointerS = ((Scode_pointerS) + 1);
          arg3K0 = (Scode_pointerS);
          goto L36237;}
        else {
          goto L64879;}}
      else {
        goto L64879;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_124:
#else
    case 124 : 
#endif
      {
      arg2_1488X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((3 == (3 & arg2_1488X))) {
        if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1488X))))), 2))))) {
          if ((0 == (3 & (SvalS)))) {
            index_1489X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
            len_1490X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg2_1488X))))), 8)) / 4;
            if ((index_1489X < 0)) {
              goto L60769;}
            else {
              if ((index_1489X < len_1490X)) {
                arg0K0 = 0;
                arg0K1 = 0;
                arg0K2 = 0;
                goto L60797;}
              else {
                goto L60769;}}}
          else {
            goto L64353;}}
        else {
          goto L64353;}}
      else {
        goto L64353;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_125:
#else
    case 125 : 
#endif
      {
      arg2_1491X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg3_1492X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((3 == (3 & arg3_1492X))) {
        if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg3_1492X))))), 2))))) {
          if ((0 == (3 & arg2_1491X))) {
            if ((9 == (255 & (SvalS)))) {
              index_1493X = PS_SHIFT_RIGHT_INLINE(arg2_1491X, 2);
              Kchar_1494X = PS_SHIFT_RIGHT_INLINE((SvalS), 8);
              if ((3 == (3 & arg3_1492X))) {
                if ((0 == (128 & (*((long *) (((char *) (-11 + arg3_1492X)))))))) {
                  len_1495X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg3_1492X))))), 8)) / 4;
                  if ((index_1493X < 0)) {
                    goto L57907;}
                  else {
                    if ((index_1493X < len_1495X)) {
                      arg0K0 = 0;
                      arg0K1 = 0;
                      arg0K2 = Kchar_1494X;
                      goto L57971;}
                    else {
                      goto L57907;}}}
                else {
                  goto L57886;}}
              else {
                goto L57886;}}
            else {
              goto L63025;}}
          else {
            goto L63025;}}
        else {
          goto L63025;}}
      else {
        goto L63025;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_126:
#else
    case 126 : 
#endif
      {
      arg2_1496X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg3_1497X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg4_1498X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg5_1499X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((3 == (3 & arg5_1499X))) {
        if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg5_1499X))))), 2))))) {
          if ((0 == (3 & arg4_1498X))) {
            if ((3 == (3 & arg3_1497X))) {
              if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg3_1497X))))), 2))))) {
                if ((0 == (3 & (arg2_1496X | (SvalS))))) {
                  from_index_1500X = PS_SHIFT_RIGHT_INLINE(arg4_1498X, 2);
                  to_index_1501X = PS_SHIFT_RIGHT_INLINE(arg2_1496X, 2);
                  count_1502X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
                  if ((from_index_1500X < 0)) {
                    goto L40710;}
                  else {
                    y_1503X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg5_1499X))))), 8)) / 4;
                    if ((y_1503X < (from_index_1500X + count_1502X))) {
                      goto L40710;}
                    else {
                      if ((to_index_1501X < 0)) {
                        goto L40710;}
                      else {
                        y_1504X = (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg3_1497X))))), 8)) / 4;
                        if ((y_1504X < (to_index_1501X + count_1502X))) {
                          goto L40710;}
                        else {
                          if ((3 == (3 & arg3_1497X))) {
                            if ((0 == (128 & (*((long *) (((char *) (-11 + arg3_1497X)))))))) {
                              if ((count_1502X < 0)) {
                                goto L40710;}
                              else {
                                memmove((void *)((((char *) (-3 + arg3_1497X))) + (PS_SHIFT_LEFT_INLINE(to_index_1501X, 2))), (void *)((((char *) (-3 + arg5_1499X))) + (PS_SHIFT_LEFT_INLINE(from_index_1500X, 2))),(PS_SHIFT_LEFT_INLINE(count_1502X, 2)));
                                SvalS = 13;
                                Scode_pointerS = ((Scode_pointerS) + 1);
                                arg3K0 = (Scode_pointerS);
                                goto L36237;}}
                            else {
                              goto L40710;}}
                          else {
                            goto L40710;}}}}}}
                else {
                  goto L46607;}}
              else {
                goto L46607;}}
            else {
              goto L46607;}}
          else {
            goto L46607;}}
        else {
          goto L46607;}}
      else {
        goto L46607;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_127:
#else
    case 127 : 
#endif
      {s48_make_availableAgc(24);
      obj_1505X = SvalS;
      if ((3 == (3 & obj_1505X))) {
        if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_1505X))))), 2))))) {
          table_1506X = Sthe_symbol_tableS;
          string_1507X = SvalS;
          v_1508X = Haction5350(string_1507X);
          index_1509X = 1023 & v_1508X;
          link_1510X = *((long *) ((((char *) (-3 + table_1506X))) + (PS_SHIFT_LEFT_INLINE(index_1509X, 3))));
          if ((0 == (3 & link_1510X))) {
            arg0K0 = (3 + (-4 & link_1510X));
            goto L30760;}
          else {
            arg0K0 = link_1510X;
            goto L30760;}}
        else {
          goto L47811;}}
      else {
        goto L47811;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_128:
#else
    case 128 : 
#endif
      {
      obj_1511X = SvalS;
      if ((3 == (3 & obj_1511X))) {
        if ((4 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_1511X))))), 2))))) {
          x_1512X = SvalS;
          descriptor_1513X = *((long *) ((((char *) (-3 + x_1512X))) + 8));
          if ((17 == (255 & descriptor_1513X))) {
            if ((529 == (*((long *) ((((char *) (-3 + x_1512X))) + 8))))) {
              arg0K0 = 5;
              goto L62581;}
            else {
              arg0K0 = 1;
              goto L62581;}}
          else {
            arg0K0 = 5;
            goto L62581;}}
        else {
          goto L62562;}}
      else {
        goto L62562;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_129:
#else
    case 129 : 
#endif
      {
      arg2_1514X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((3 == (3 & arg2_1514X))) {
        if ((4 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1514X))))), 2))))) {
          x_1515X = SvalS;
          if ((1 == x_1515X)) {
            goto L57509;}
          else {
            if ((5 == x_1515X)) {
              goto L57509;}
            else {
              goto L57516;}}}
        else {
          goto L57516;}}
      else {
        goto L57516;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_130:
#else
    case 130 : 
#endif
      {
      x_1516X = SvalS;
      if ((3 == (3 & x_1516X))) {
        if ((0 == (128 & (*((long *) (((char *) (-11 + x_1516X)))))))) {
          arg0K0 = 1;
          goto L67858;}
        else {
          arg0K0 = 5;
          goto L67858;}}
      else {
        arg0K0 = 5;
        goto L67858;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_131:
#else
    case 131 : 
#endif
      {
      x_1517X = SvalS;
      if ((3 == (3 & x_1517X))) {
        if ((0 == (128 & (*((long *) (((char *) (-11 + x_1517X)))))))) {
          *((long *) (((char *) (-11 + x_1517X)))) = (long) ((128 | (*((long *) (((char *) (-11 + x_1517X)))))));
          goto L67871;}
        else {
          goto L67871;}}
      else {
        goto L67871;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_132:
#else
    case 132 : 
#endif
      {s48_make_availableAgc(64);
      arg2_1518X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg3_1519X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg4_1520X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((0 == (3 & arg2_1518X))) {
        mode_1521X = PS_SHIFT_RIGHT_INLINE(arg2_1518X, 2);
        close_silentlyP_1522X = SvalS;
        if ((1 == mode_1521X)) {
          goto L52434;}
        else {
          if ((2 == mode_1521X)) {
            goto L52434;}
          else {
            if ((3 == mode_1521X)) {
              goto L52434;}
            else {
              if ((4 == mode_1521X)) {
                goto L52434;}
              else {push_exception_setupB(5, 1);
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) (arg4_1520X);
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(mode_1521X, 2)));
                arg0K0 = 2;
                goto L33796;}}}}}
      else {push_exception_setupB(5, 1);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg4_1520X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg3_1519X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg2_1518X);
        x_1523X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1523X);
        arg0K0 = 4;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_133:
#else
    case 133 : 
#endif
      {
      obj_1524X = SvalS;
      if ((3 == (3 & obj_1524X))) {
        if ((6 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_1524X))))), 2))))) {
          channel_1525X = SvalS;
          if ((0 == (*((long *) (((char *) (-3 + channel_1525X))))))) {push_exception_setupB(5, 1);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (channel_1525X);
            arg0K0 = 1;
            goto L33796;}
          else {
            status_1526X = close_channelB(channel_1525X);
            if ((status_1526X == NO_ERRORS)) {
              SvalS = 13;
              Scode_pointerS = ((Scode_pointerS) + 1);
              arg3K0 = (Scode_pointerS);
              goto L36237;}
            else {push_exception_setupB(25, 1);
              SstackS = ((SstackS) + -8);
              *((long *) (SstackS)) = (long) (channel_1525X);
              SstackS = ((SstackS) + -8);
              *((long *) (SstackS)) = (long) (status_1526X);
              arg0K0 = 2;
              goto L33796;}}}
        else {
          goto L67888;}}
      else {
        goto L67888;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_134:
#else
    case 134 : 
#endif
      {s48_make_availableAgc(16);
      arg2_1527X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg3_1528X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg4_1529X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg5_1530X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((3 == (3 & arg5_1530X))) {
        if ((6 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg5_1530X))))), 2))))) {
          if ((0 == (3 & (arg3_1528X | arg2_1527X)))) {
            x_1531X = SvalS;
            if ((1 == x_1531X)) {
              goto L61061;}
            else {
              if ((5 == x_1531X)) {
                goto L61061;}
              else {
                goto L61072;}}}
          else {
            goto L61072;}}
        else {
          goto L61072;}}
      else {
        goto L61072;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_135:
#else
    case 135 : 
#endif
      {s48_make_availableAgc(16);
      arg2_1532X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg3_1533X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg4_1534X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((3 == (3 & arg4_1534X))) {
        if ((6 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg4_1534X))))), 2))))) {
          if ((0 == (3 & (arg2_1532X | (SvalS))))) {
            start_1535X = PS_SHIFT_RIGHT_INLINE(arg2_1532X, 2);
            count_1536X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
            v_1537X = 8 == (*((long *) (((char *) (-3 + arg4_1534X)))));
            if (v_1537X) {
              if ((3 == (3 & arg3_1533X))) {
                if ((17 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg3_1533X))))), 2))))) {
                  if (((PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg3_1533X))))), 8)) < (start_1535X + count_1536X))) {
                    goto L53067;}
                  else {
                    got_1538X = ps_write_fd((PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + arg4_1534X))) + 16))), 2)), ((((char *) (-3 + arg3_1533X))) + start_1535X), count_1536X, &pendingP_1539X, &status_1540X);
                    if ((status_1540X == NO_ERRORS)) {
                      if (pendingP_1539X) {
                        addr_1541X = (((char *) (-3 + arg4_1534X))) + 40;S48_WRITE_BARRIER(arg4_1534X, addr_1541X, 5);
                        *((long *) addr_1541X) = (long) (5);
                        arg0K0 = 1;
                        goto L53066;}
                      else {
                        arg0K0 = (PS_SHIFT_LEFT_INLINE(got_1538X, 2));
                        goto L53066;}}
                    else {
                      addr_1542X = s48_allocate_small(16);
                      *((long *) addr_1542X) = (long) (2070);
                      x_1543X = 3 + (((long) (addr_1542X + 8)));
                      *((long *) (((char *) (-3 + x_1543X)))) = (long) ((PS_SHIFT_LEFT_INLINE(status_1540X, 2)));
                      arg0K0 = x_1543X;
                      goto L53066;}}}
                else {
                  goto L53067;}}
              else {
                goto L53067;}}
            else {
              goto L53067;}}
          else {
            goto L61275;}}
        else {
          goto L61275;}}
      else {
        goto L61275;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_136:
#else
    case 136 : 
#endif
      {
      if ((0 == (3 & (SvalS)))) {
        param_1544X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
        if ((0 == param_1544X)) {
          x_1545X = ps_io_buffer_size();
          SvalS = (PS_SHIFT_LEFT_INLINE(x_1545X, 2));
          Scode_pointerS = ((Scode_pointerS) + 1);
          arg3K0 = (Scode_pointerS);
          goto L36237;}
        else {
          if ((1 == param_1544X)) {
            x_1546X = ps_io_crlf_p();
            if (x_1546X) {
              arg0K0 = 5;
              goto L64050;}
            else {
              arg0K0 = 1;
              goto L64050;}}
          else {push_exception_setupB(18, 1);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(param_1544X, 2)));
            arg0K0 = 1;
            goto L33796;}}}
      else {push_exception_setupB(5, 1);
        x_1547X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1547X);
        arg0K0 = 1;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_137:
#else
    case 137 : 
#endif
      {
      obj_1548X = SvalS;
      if ((3 == (3 & obj_1548X))) {
        if ((6 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_1548X))))), 2))))) {
          channel_1549X = SvalS;
          if ((0 == (*((long *) (((char *) (-3 + channel_1549X))))))) {push_exception_setupB(5, 1);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (channel_1549X);
            arg0K0 = 1;
            goto L33796;}
          else {
            readyP_1550X = ps_check_fd((PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + channel_1549X))) + 16))), 2)), (4 == (*((long *) (((char *) (-3 + channel_1549X)))))), &status_1551X);
            if ((status_1551X == NO_ERRORS)) {
              if (readyP_1550X) {
                arg0K0 = 5;
                goto L57062;}
              else {
                arg0K0 = 1;
                goto L57062;}}
            else {push_exception_setupB(25, 1);
              SstackS = ((SstackS) + -8);
              *((long *) (SstackS)) = (long) (channel_1549X);
              SstackS = ((SstackS) + -8);
              *((long *) (SstackS)) = (long) (status_1551X);
              arg0K0 = 2;
              goto L33796;}}}
        else {
          goto L67921;}}
      else {
        goto L67921;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_138:
#else
    case 138 : 
#endif
      {
      obj_1552X = SvalS;
      if ((3 == (3 & obj_1552X))) {
        if ((6 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_1552X))))), 2))))) {
          channel_1553X = SvalS;
          head_1554X = Spending_channels_headS;
          if ((1 == head_1554X)) {
            addr_1555X = (((char *) (-3 + channel_1553X))) + 40;S48_WRITE_BARRIER(channel_1553X, addr_1555X, 1);
            *((long *) addr_1555X) = (long) (1);
            n_1556X = ps_abort_fd_op((PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + channel_1553X))) + 16))), 2)));
            arg0K0 = (PS_SHIFT_LEFT_INLINE(n_1556X, 2));
            goto L61423;}
          else {
            if ((channel_1553X == head_1554X)) {
              channel_1557X = Spending_channels_headS;
              next_1558X = *((long *) ((((char *) (-3 + channel_1557X))) + 32));
              Spending_channels_headS = next_1558X;
              addr_1559X = (((char *) (-3 + channel_1557X))) + 32;S48_WRITE_BARRIER(channel_1557X, addr_1559X, 1);
              *((long *) addr_1559X) = (long) (1);
              if ((1 == next_1558X)) {
                Spending_channels_tailS = 1;
                goto L17657;}
              else {
                goto L17657;}}
            else {
              arg0K0 = (*((long *) ((((char *) (-3 + head_1554X))) + 32)));
              arg0K1 = head_1554X;
              goto L17675;}}}
        else {
          goto L61406;}}
      else {
        goto L61406;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_139:
#else
    case 139 : 
#endif
      {s48_make_availableAgc((PS_SHIFT_LEFT_INLINE((3 * (Snumber_of_channelsS)), 3)));
      arg0K0 = (-1 + (Snumber_of_channelsS));
      arg0K1 = 25;
      goto L24789;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_140:
#else
    case 140 : 
#endif
      {
      addr_1560X = s48_allocate_weakAgc(16);
      *((long *) addr_1560X) = (long) (2102);
      weak_pointer_1561X = 3 + (((long) (addr_1560X + 8)));
      *((long *) (((char *) (-3 + weak_pointer_1561X)))) = (long) ((SvalS));
      SvalS = weak_pointer_1561X;
      Scode_pointerS = ((Scode_pointerS) + 1);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_142:
#else
    case 142 : 
#endif
      {
      SvalS = (*((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24)));
      Scode_pointerS = ((Scode_pointerS) + 1);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_143:
#else
    case 143 : 
#endif
      {
      proposal_1562X = SvalS;
      if ((1 == proposal_1562X)) {
        goto L53288;}
      else {
        if ((3 == (3 & proposal_1562X))) {
          if ((2 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + proposal_1562X))))), 2))))) {
            if ((4 == (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + proposal_1562X))))), 8))), 3)))) {
              if ((1 == (*((long *) (((char *) (-3 + proposal_1562X))))))) {
                goto L53288;}
              else {
                goto L53319;}}
            else {
              goto L53319;}}
          else {
            goto L53319;}}
        else {
          goto L53319;}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_144:
#else
    case 144 : 
#endif
      {
      proposal_1563X = *((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24));
      if ((1 == proposal_1563X)) {push_exception_setupB(27, 1);
        arg0K0 = 0;
        goto L33796;}
      else {GET_PROPOSAL_LOCK();
        log_1564X = *((long *) ((((char *) (-3 + proposal_1563X))) + 8));
        arg0K0 = 0;
        goto L14777;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_145:
#else
    case 145 : 
#endif
      {
      stob_1565X = SvalS;
      type_1566X = *((unsigned char *) ((Scode_pointerS) + 1));
      offset_1567X = *((unsigned char *) ((Scode_pointerS) + 2));
      if ((3 == (3 & stob_1565X))) {
        if (((31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + stob_1565X))))), 2))) == type_1566X)) {
          x_1568X = *((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24));
          if ((1 == x_1568X)) {
            arg0K0 = (*((long *) ((((char *) (-3 + stob_1565X))) + (PS_SHIFT_LEFT_INLINE(offset_1567X, 3)))));
            goto L40994;}
          else {
            merged_arg0K0 = stob_1565X;
            merged_arg0K1 = (PS_SHIFT_LEFT_INLINE(offset_1567X, 2));
#ifdef USE_DIRECT_THREADING
            proposal_d_read_return_address = &&proposal_d_read_return_1;
#else
            proposal_d_read_return_tag = 1;
#endif
            goto proposal_d_read;
           proposal_d_read_return_1:
            v_1569X = proposal_d_read0_return_value;
            arg0K0 = v_1569X;
            goto L40994;}}
        else {
          goto L40995;}}
      else {
        goto L40995;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_146:
#else
    case 146 : 
#endif
      {
      arg2_1570X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg3_1571X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg4_1572X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg5_1573X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((3 == (3 & arg5_1573X))) {
        if ((17 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg5_1573X))))), 2))))) {
          if ((0 == (3 & arg4_1572X))) {
            if ((3 == (3 & arg3_1571X))) {
              if ((17 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg3_1571X))))), 2))))) {
                if ((0 == (3 & (arg2_1570X | (SvalS))))) {
                  from_index_1574X = PS_SHIFT_RIGHT_INLINE(arg4_1572X, 2);
                  to_index_1575X = PS_SHIFT_RIGHT_INLINE(arg2_1570X, 2);
                  count_1576X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
                  v_1577X = *((unsigned char *) ((Scode_pointerS) + 1));
                  if ((from_index_1574X < 0)) {
                    goto L41088;}
                  else {
                    if (((PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg5_1573X))))), 8)) < (from_index_1574X + count_1576X))) {
                      goto L41088;}
                    else {
                      if ((to_index_1575X < 0)) {
                        goto L41088;}
                      else {
                        if (((PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg3_1571X))))), 8)) < (to_index_1575X + count_1576X))) {
                          goto L41088;}
                        else {
                          if ((count_1576X < 0)) {
                            goto L41088;}
                          else {
                            if ((3 == (3 & arg3_1571X))) {
                              if ((0 == (128 & (*((long *) (((char *) (-11 + arg3_1571X)))))))) {
                                if ((0 == v_1577X)) {
                                  goto L41164;}
                                else {
                                  if ((1 == (*((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24))))) {
                                    goto L41164;}
                                  else {
                                    arg0K0 = 4096;
                                    arg0K1 = (*((long *) ((((char *) (-3 + (*((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24)))))) + 24)));
                                    goto L41307;}}}
                              else {
                                goto L41132;}}
                            else {
                              goto L41132;}}}}}}}
                else {
                  goto L46873;}}
              else {
                goto L46873;}}
            else {
              goto L46873;}}
          else {
            goto L46873;}}
        else {
          goto L46873;}}
      else {
        goto L46873;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_147:
#else
    case 147 : 
#endif
      {
      arg2_1578X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((3 == (3 & arg2_1578X))) {
        if ((17 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1578X))))), 2))))) {
          if ((0 == (3 & (SvalS)))) {
            index_1579X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
            len_1580X = PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg2_1578X))))), 8);
            if ((index_1579X < 0)) {
              goto L41534;}
            else {
              if ((index_1579X < len_1580X)) {
                x_1581X = *((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24));
                if ((1 == x_1581X)) {
                  arg0K0 = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((((char *) (-3 + arg2_1578X))) + index_1579X))), 2));
                  goto L41533;}
                else {
                  index_1582X = PS_SHIFT_LEFT_INLINE(index_1579X, 2);
                  log_1583X = *((long *) ((((char *) (-3 + (*((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24)))))) + 16));
                  arg0K0 = 0;
                  goto L24530;}}
              else {
                goto L41534;}}}
          else {
            goto L47069;}}
        else {
          goto L47069;}}
      else {
        goto L47069;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_148:
#else
    case 148 : 
#endif
      {
      arg2_1584X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg3_1585X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((3 == (3 & arg3_1585X))) {
        if ((17 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg3_1585X))))), 2))))) {
          if ((0 == (3 & arg2_1584X))) {
            index_1586X = PS_SHIFT_RIGHT_INLINE(arg2_1584X, 2);
            byte_1587X = SvalS;
            if ((3 == (3 & arg3_1585X))) {
              if ((0 == (128 & (*((long *) (((char *) (-11 + arg3_1585X)))))))) {
                if ((0 == (3 & byte_1587X))) {
                  len_1588X = PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg3_1585X))))), 8);
                  if ((index_1586X < 0)) {
                    goto L41664;}
                  else {
                    if ((index_1586X < len_1588X)) {
                      x_1589X = *((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24));
                      if ((1 == x_1589X)) {
                        *((unsigned char *) ((((char *) (-3 + arg3_1585X))) + index_1586X)) = (unsigned char) ((PS_SHIFT_RIGHT_INLINE(byte_1587X, 2)));
                        goto L41663;}
                      else {
                        index_1590X = PS_SHIFT_LEFT_INLINE(index_1586X, 2);
                        log_1591X = *((long *) ((((char *) (-3 + (*((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24)))))) + 16));
                        arg0K0 = 0;
                        goto L24706;}}
                    else {
                      goto L41664;}}}
                else {push_exception_setupB(5, 1);
                  SstackS = ((SstackS) + -8);
                  *((long *) (SstackS)) = (long) (arg3_1585X);
                  SstackS = ((SstackS) + -8);
                  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(index_1586X, 2)));
                  SstackS = ((SstackS) + -8);
                  *((long *) (SstackS)) = (long) (byte_1587X);
                  arg0K0 = 3;
                  goto L33796;}}
              else {
                goto L41613;}}
            else {
              goto L41613;}}
          else {
            goto L47174;}}
        else {
          goto L47174;}}
      else {
        goto L47174;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_149:
#else
    case 149 : 
#endif
      {
      SvalS = 529;
      Scode_pointerS = ((Scode_pointerS) + 1);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_150:
#else
    case 150 : 
#endif
      {
      SvalS = 13;
      Scode_pointerS = ((Scode_pointerS) + 1);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_151:
#else
    case 151 : 
#endif
      {
      x_1592X = SvalS;push_exception_setupB(16, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1592X);
      arg0K0 = 1;
      goto L33796;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_152:
#else
    case 152 : 
#endif
      {
      SvalS = 1;
      Scode_pointerS = ((Scode_pointerS) + 1);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_153:
#else
    case 153 : 
#endif
      {
      SvalS = 21;
      Scode_pointerS = ((Scode_pointerS) + 1);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_154:
#else
    case 154 : 
#endif
      {
      arg2_1593X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg3_1594X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg4_1595X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((3 == (3 & arg4_1595X))) {
        if ((17 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg4_1595X))))), 2))))) {
          if ((3 == (3 & arg2_1593X))) {
            if ((17 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1593X))))), 2))))) {
              obj_1596X = SvalS;
              if ((3 == (3 & obj_1596X))) {
                if ((2 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_1596X))))), 2))))) {
                  undumpables_1597X = SvalS;
                  port_1598X = ps_open_output_file((((char *)(((char *) (-3 + arg4_1595X))))), &status_1599X);
                  if ((status_1599X == NO_ERRORS)) {
                    status_1600X = ps_write_string((((char *)(((char *) (-3 + arg2_1593X))))), port_1598X);
                    if ((status_1600X == NO_ERRORS)) {
                      status_1601X = s48_write_image(arg3_1594X, undumpables_1597X, port_1598X);
                      if ((status_1601X == NO_ERRORS)) {
                        status_1602X = ps_close(port_1598X);
                        if ((status_1602X == NO_ERRORS)) {
                          SvalS = 13;
                          Scode_pointerS = ((Scode_pointerS) + 1);
                          arg3K0 = (Scode_pointerS);
                          goto L36237;}
                        else {
                          arg0K0 = status_1602X;
                          goto L58140;}}
                      else {
                        close_status_1603X = ps_close(port_1598X);
                        if ((close_status_1603X == NO_ERRORS)) {
                          arg0K0 = status_1601X;
                          goto L58140;}
                        else {
                          arg0K0 = close_status_1603X;
                          goto L58140;}}}
                    else {
                      close_status_1604X = ps_close(port_1598X);
                      if ((close_status_1604X == NO_ERRORS)) {
                        arg0K0 = status_1600X;
                        goto L58140;}
                      else {
                        arg0K0 = close_status_1604X;
                        goto L58140;}}}
                  else {
                    arg0K0 = status_1599X;
                    goto L58140;}}
                else {
                  goto L63210;}}
              else {
                goto L63210;}}
            else {
              goto L63210;}}
          else {
            goto L63210;}}
        else {
          goto L63210;}}
      else {
        goto L63210;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_155:
#else
    case 155 : 
#endif
      {
      SvalS = 13;s48_collect(1);
      Scode_pointerS = ((Scode_pointerS) + 1);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_156:
#else
    case 156 : 
#endif
      {
      obj_1605X = SvalS;
      if ((3 == (3 & obj_1605X))) {
        if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_1605X))))), 2))))) {
          x_1606X = Haction5350((SvalS));
          SvalS = (PS_SHIFT_LEFT_INLINE(x_1606X, 2));
          Scode_pointerS = ((Scode_pointerS) + 1);
          arg3K0 = (Scode_pointerS);
          goto L36237;}
        else {
          goto L63918;}}
      else {
        goto L63918;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_157:
#else
    case 157 : 
#endif
      {s48_make_availableAgc(48);
      arg2_1607X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      proc_1608X = SvalS;
      if ((3 == (3 & arg2_1607X))) {
        if ((3 == (3 & proc_1608X))) {
          if ((3 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + proc_1608X))))), 2))))) {GET_PROPOSAL_LOCK();
            addr_1609X = s48_allocate_small(24);
            *((long *) addr_1609X) = (long) (4098);
            x_1610X = 3 + (((long) (addr_1609X + 8)));
            *((long *) (((char *) (-3 + x_1610X)))) = (long) (arg2_1607X);
            *((long *) ((((char *) (-3 + x_1610X))) + 8)) = (long) (proc_1608X);
            b_1611X = SHARED_REF((Sfinalizer_alistS));
            addr_1612X = s48_allocate_small(24);
            *((long *) addr_1612X) = (long) (4098);
            x_1613X = 3 + (((long) (addr_1612X + 8)));
            *((long *) (((char *) (-3 + x_1613X)))) = (long) (x_1610X);
            *((long *) ((((char *) (-3 + x_1613X))) + 8)) = (long) (b_1611X);SHARED_SETB((Sfinalizer_alistS), x_1613X);RELEASE_PROPOSAL_LOCK();
            SvalS = 13;
            Scode_pointerS = ((Scode_pointerS) + 1);
            arg3K0 = (Scode_pointerS);
            goto L36237;}
          else {
            goto L58396;}}
        else {
          goto L58396;}}
      else {
        goto L58396;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_158:
#else
    case 158 : 
#endif
      {
      arg2_1614X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((0 == (3 & arg2_1614X))) {
        key_1615X = PS_SHIFT_RIGHT_INLINE(arg2_1614X, 2);
        other_1616X = SvalS;
        if ((6 == key_1615X)) {
          SvalS = (-4 & other_1616X);
          Scode_pointerS = ((Scode_pointerS) + 1);
          arg3K0 = (Scode_pointerS);
          goto L36237;}
        else {
          if ((0 == key_1615X)) {
            x_1617X = s48_available();
            SvalS = (PS_SHIFT_LEFT_INLINE(x_1617X, 2));
            Scode_pointerS = ((Scode_pointerS) + 1);
            arg3K0 = (Scode_pointerS);
            goto L36237;}
          else {
            if ((1 == key_1615X)) {
              bytes_1618X = s48_heap_size();
              SvalS = (-4 & (PS_SHIFT_RIGHT_INLINE((7 + bytes_1618X), 1)));
              Scode_pointerS = ((Scode_pointerS) + 1);
              arg3K0 = (Scode_pointerS);
              goto L36237;}
            else {
              if ((2 == key_1615X)) {
                x_1619X = s48_max_heap_size();
                SvalS = (PS_SHIFT_LEFT_INLINE(x_1619X, 2));
                Scode_pointerS = ((Scode_pointerS) + 1);
                arg3K0 = (Scode_pointerS);
                goto L36237;}
              else {
                if ((3 == key_1615X)) {
                  SvalS = (PS_SHIFT_LEFT_INLINE(((Sstack_endS) - (Sstack_beginS)), 2));
                  Scode_pointerS = ((Scode_pointerS) + 1);
                  arg3K0 = (Scode_pointerS);
                  goto L36237;}
                else {
                  if ((4 == key_1615X)) {
                    x_1620X = s48_gc_count();
                    SvalS = (PS_SHIFT_LEFT_INLINE(x_1620X, 2));
                    Scode_pointerS = ((Scode_pointerS) + 1);
                    arg3K0 = (Scode_pointerS);
                    goto L36237;}
                  else {
                    if ((5 == key_1615X)) {push_exception_setupB(15, 1);
                      SstackS = ((SstackS) + -8);
                      *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(key_1615X, 2)));
                      SstackS = ((SstackS) + -8);
                      *((long *) (SstackS)) = (long) (other_1616X);
                      arg0K0 = 2;
                      goto L33796;}
                    else {push_exception_setupB(18, 1);
                      SstackS = ((SstackS) + -8);
                      *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(key_1615X, 2)));
                      SstackS = ((SstackS) + -8);
                      *((long *) (SstackS)) = (long) (other_1616X);
                      arg0K0 = 2;
                      goto L33796;}}}}}}}}
      else {push_exception_setupB(5, 1);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg2_1614X);
        x_1621X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1621X);
        arg0K0 = 2;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_159:
#else
    case 159 : 
#endif
      {
      if ((0 == (3 & (SvalS)))) {
        type_1622X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
        arg4K0 = 1;
        goto L61542;}
      else {push_exception_setupB(5, 1);
        x_1623X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1623X);
        arg0K0 = 1;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_160:
#else
    case 160 : 
#endif
      {
      x_1624X = SvalS;
      arg4K0 = 1;
      arg0K1 = x_1624X;
      goto L68041;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_161:
#else
    case 161 : 
#endif
      {
      SvalS = (Scurrent_threadS);
      Scode_pointerS = ((Scode_pointerS) + 1);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_162:
#else
    case 162 : 
#endif
      {
      Scurrent_threadS = (SvalS);
      SvalS = 13;
      Scode_pointerS = ((Scode_pointerS) + 1);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_163:
#else
    case 163 : 
#endif
      {
      val_1625X = SHARED_REF((Ssession_dataS));
      SvalS = val_1625X;
      Scode_pointerS = ((Scode_pointerS) + 1);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_164:
#else
    case 164 : 
#endif
      {SHARED_SETB((Ssession_dataS), (SvalS));
      SvalS = 13;
      Scode_pointerS = ((Scode_pointerS) + 1);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_165:
#else
    case 165 : 
#endif
      {
      obj_1626X = SvalS;
      if ((3 == (3 & obj_1626X))) {
        if ((2 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_1626X))))), 2))))) {
          if (((PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + (SvalS)))))), 8))), 3)) < 205)) {
            goto L37998;}
          else {
            temp_1627X = SHARED_REF((Sexception_handlersS));SHARED_SETB((Sexception_handlersS), (SvalS));
            SvalS = temp_1627X;
            Scode_pointerS = ((Scode_pointerS) + 1);
            arg3K0 = (Scode_pointerS);
            goto L36237;}}
        else {
          goto L37998;}}
      else {
        goto L37998;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_166:
#else
    case 166 : 
#endif
      {
      data_1628X = 3 + (((long) (SstackS)));
      SstackS = ((SstackS) + 40);
      code_1629X = *((long *) ((((char *) (-3 + data_1628X))) + 16));
      exception_1630X = *((long *) ((((char *) (-3 + data_1628X))) + 24));
      size_1631X = *((long *) ((((char *) (-3 + data_1628X))) + 32));
      pc_1632X = PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + data_1628X))) + 8))), 2);
      opcode_1633X = *((unsigned char *) ((((char *) (-3 + code_1629X))) + pc_1632X));
      if ((opcode_1633X < 55)) {
        if ((4 == opcode_1633X)) {
          goto L36319;}
        else {
          if ((5 == opcode_1633X)) {
            goto L36319;}
          else {
            Slast_code_calledS = code_1629X;
            Scode_pointerS = ((((char *) (-3 + code_1629X))) + pc_1632X);push_exception_setupB(29, 1);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (exception_1630X);
            arg0K0 = 1;
            goto L33796;}}}
      else {
        goto L36319;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_167:
#else
    case 167 : 
#endif
      {
      data_1634X = 3 + (((long) (SstackS)));
      SstackS = ((SstackS) + 32);
      exception_1635X = *((long *) ((((char *) (-3 + data_1634X))) + 8));
      bc_code_1636X = *((long *) ((((char *) (-3 + data_1634X))) + 24));
      bc_pc_1637X = PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + data_1634X))) + 16))), 2);
      opcode_1638X = *((unsigned char *) ((((char *) (-3 + bc_code_1636X))) + bc_pc_1637X));
      if ((opcode_1638X < 55)) {
        if ((4 == opcode_1638X)) {
          goto L34059;}
        else {
          if ((5 == opcode_1638X)) {
            goto L34059;}
          else {
            Slast_code_calledS = bc_code_1636X;
            Scode_pointerS = ((((char *) (-3 + bc_code_1636X))) + bc_pc_1637X);push_exception_setupB(29, 1);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (exception_1635X);
            arg0K0 = 1;
            goto L33796;}}}
      else {
        goto L34059;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_168:
#else
    case 168 : 
#endif
      {
      obj_1639X = SvalS;
      if ((3 == (3 & obj_1639X))) {
        if ((2 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_1639X))))), 2))))) {
          if (((PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + (SvalS)))))), 8))), 3)) < 7)) {
            goto L36888;}
          else {
            temp_1640X = SHARED_REF((Sinterrupt_handlersS));SHARED_SETB((Sinterrupt_handlersS), (SvalS));
            SvalS = temp_1640X;
            Scode_pointerS = ((Scode_pointerS) + 1);
            arg3K0 = (Scode_pointerS);
            goto L36237;}}
        else {
          goto L36888;}}
      else {
        goto L36888;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_169:
#else
    case 169 : 
#endif
      {
      old_1641X = Senabled_interruptsS;
      p_1642X = SvalS;
      Senabled_interruptsS = (PS_SHIFT_RIGHT_INLINE(p_1642X, 2));
      if ((0 == ((Spending_interruptsS) & (Senabled_interruptsS)))) {
        s48_Sstack_limitS = (Sreal_stack_limitS);
        if ((s48_Spending_eventsPS)) {
          s48_Sstack_limitS = (((char *) -1));
          goto L68089;}
        else {
          goto L68089;}}
      else {
        s48_Sstack_limitS = (((char *) -1));
        goto L68089;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_170:
#else
    case 170 : 
#endif
      {
      SstackS = ((SstackS) + 8);
#ifdef USE_DIRECT_THREADING
      s48_pop_interrupt_state_return_address = &&s48_pop_interrupt_state_return_0;
#else
      s48_pop_interrupt_state_return_tag = 0;
#endif
      goto s48_pop_interrupt_state;
     s48_pop_interrupt_state_return_0:
      pc_1643X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      code_1644X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      Slast_code_calledS = code_1644X;
      Scode_pointerS = ((((char *) (-3 + code_1644X))) + (PS_SHIFT_RIGHT_INLINE(pc_1643X, 2)));
      v_1645X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      SvalS = v_1645X;
      arg3K0 = (Scode_pointerS);
      goto L36237;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_171:
#else
    case 171 : 
#endif
      {
      SstackS = ((SstackS) + 8);
#ifdef USE_DIRECT_THREADING
      s48_pop_interrupt_state_return_address = &&s48_pop_interrupt_state_return_1;
#else
      s48_pop_interrupt_state_return_tag = 1;
#endif
      goto s48_pop_interrupt_state;
     s48_pop_interrupt_state_return_1:
      v_1646X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      SvalS = v_1646X;
      p_1647X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      v_1648X = s48_call_native_procedure((SvalS), (PS_SHIFT_RIGHT_INLINE(p_1647X, 2)));
      arg0K0 = v_1648X;
      goto L65708;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_172:
#else
    case 172 : 
#endif
      {
      SstackS = ((SstackS) + 8);
#ifdef USE_DIRECT_THREADING
      s48_pop_interrupt_state_return_address = &&s48_pop_interrupt_state_return_2;
#else
      s48_pop_interrupt_state_return_tag = 2;
#endif
      goto s48_pop_interrupt_state;
     s48_pop_interrupt_state_return_2:
      return_address_1649X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      template_1650X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      v_1651X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      SvalS = v_1651X;
      v_1652X = s48_jump_to_native_address(return_address_1649X, template_1650X);
      arg0K0 = v_1652X;
      goto L65708;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_173:
#else
    case 173 : 
#endif
      {
      if ((0 == (3 & (SvalS)))) {
        p_1653X = SvalS;
        Spending_interruptsS = (-2 & (Spending_interruptsS));
        if ((0 == ((Spending_interruptsS) & (Senabled_interruptsS)))) {
          s48_Sstack_limitS = (Sreal_stack_limitS);
          if ((s48_Spending_eventsPS)) {
            s48_Sstack_limitS = (((char *) -1));
            goto L65044;}
          else {
            goto L65044;}}
        else {
          s48_Sstack_limitS = (((char *) -1));
          goto L65044;}}
      else {push_exception_setupB(5, 1);
        x_1654X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1654X);
        arg0K0 = 1;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_174:
#else
    case 174 : 
#endif
      {
      arg2_1655X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((0 == (3 & arg2_1655X))) {
        x_1656X = SvalS;
        if ((1 == x_1656X)) {
          goto L62774;}
        else {
          if ((5 == x_1656X)) {
            goto L62774;}
          else {
            goto L62779;}}}
      else {
        goto L62779;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_175:
#else
    case 175 : 
#endif
      {
      p_1657X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      nargs_1658X = PS_SHIFT_RIGHT_INLINE(p_1657X, 2);
      p_1659X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      rest_list_1660X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((61 < nargs_1658X)) {push_exception_setupB(20, 1);
        x_1661X = *((long *) ((SstackS) + (-8 + (PS_SHIFT_LEFT_INLINE((-4 & p_1659X), 1)))));
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1661X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (nargs_1658X);
        arg0K0 = 2;
        goto L33796;}
      else {
        arg0K0 = rest_list_1660X;
        goto L41875;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_176:
#else
    case 176 : 
#endif
      {
      p_1662X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      nargs_1663X = PS_SHIFT_RIGHT_INLINE(p_1662X, 2);
      p_1664X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      rest_list_1665X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((61 < nargs_1663X)) {push_exception_setupB(20, 1);
        x_1666X = *((long *) ((SstackS) + (-8 + (PS_SHIFT_LEFT_INLINE((-4 & p_1664X), 1)))));
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1666X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (nargs_1663X);
        arg0K0 = 2;
        goto L33796;}
      else {
        arg0K0 = rest_list_1665X;
        goto L42176;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_177:
#else
    case 177 : 
#endif
      {s48_make_availableAgc(40);
      arg2_1667X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((3 == (3 & arg2_1667X))) {
        if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1667X))))), 2))))) {
          x_1668X = SvalS;
          if ((1 == x_1668X)) {
            goto L61637;}
          else {
            if ((5 == x_1668X)) {
              goto L61637;}
            else {
              goto L61642;}}}
        else {
          goto L61642;}}
      else {
        goto L61642;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_178:
#else
    case 178 : 
#endif
      {
      arg2_1669X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((3 == (3 & arg2_1669X))) {
        if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1669X))))), 2))))) {
          x_1670X = SvalS;
          if ((1 == x_1670X)) {
            goto L46020;}
          else {
            if ((5 == x_1670X)) {
              goto L46020;}
            else {
              goto L46025;}}}
        else {
          goto L46025;}}
      else {
        goto L46025;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_179:
#else
    case 179 : 
#endif
      {
      arg4K0 = 1;
      goto L68151;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_180:
#else
    case 180 : 
#endif
      {
      arg_1671X = SvalS;
      if ((3 == (3 & arg_1671X))) {
        if ((14 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg_1671X))))), 2))))) {
          uid_val_1672X = *((long *) ((((char *) (-3 + arg_1671X))) + 16));
          if ((0 == (3 & uid_val_1672X))) {
            uid_1673X = PS_SHIFT_RIGHT_INLINE(uid_val_1672X, 2);
            if ((uid_1673X < (Snumber_of_event_typesS))) {
              val_1674X = PS_SHIFT_LEFT_INLINE(uid_1673X, 2);
              addr_1675X = (((char *) (-3 + arg_1671X))) + 16;S48_WRITE_BARRIER(arg_1671X, addr_1675X, val_1674X);
              *((long *) addr_1675X) = (long) (val_1674X);
              merged_arg0K0 = uid_1673X;
#ifdef USE_DIRECT_THREADING
              use_event_type_uidB_return_address = &&use_event_type_uidB_return_0;
#else
              use_event_type_uidB_return_tag = 0;
#endif
              goto use_event_type_uidB;
             use_event_type_uidB_return_0:
              arg0K0 = uid_1673X;
              goto L65352;}
            else {
              v_1676X = add_external_event_types((1 + uid_1673X));
              if (v_1676X) {
                val_1677X = PS_SHIFT_LEFT_INLINE(uid_1673X, 2);
                addr_1678X = (((char *) (-3 + arg_1671X))) + 16;S48_WRITE_BARRIER(arg_1671X, addr_1678X, val_1677X);
                *((long *) addr_1678X) = (long) (val_1677X);
                merged_arg0K0 = uid_1673X;
#ifdef USE_DIRECT_THREADING
                use_event_type_uidB_return_address = &&use_event_type_uidB_return_1;
#else
                use_event_type_uidB_return_tag = 1;
#endif
                goto use_event_type_uidB;
               use_event_type_uidB_return_1:
                arg0K0 = uid_1673X;
                goto L65352;}
              else {
                arg0K0 = -1;
                goto L65352;}}}
          else {
#ifdef USE_DIRECT_THREADING
            unused_event_type_uid_return_address = &&unused_event_type_uid_return_0;
#else
            unused_event_type_uid_return_tag = 0;
#endif
            goto unused_event_type_uid;
           unused_event_type_uid_return_0:
            uid_1679X = unused_event_type_uid0_return_value;
            if ((-1 == uid_1679X)) {
              arg0K0 = uid_1679X;
              goto L65352;}
            else {
              val_1680X = PS_SHIFT_LEFT_INLINE(uid_1679X, 2);
              addr_1681X = (((char *) (-3 + arg_1671X))) + 16;S48_WRITE_BARRIER(arg_1671X, addr_1681X, val_1680X);
              *((long *) addr_1681X) = (long) (val_1680X);
              merged_arg0K0 = uid_1679X;
#ifdef USE_DIRECT_THREADING
              use_event_type_uidB_return_address = &&use_event_type_uidB_return_2;
#else
              use_event_type_uidB_return_tag = 2;
#endif
              goto use_event_type_uidB;
             use_event_type_uidB_return_2:
              arg0K0 = uid_1679X;
              goto L65352;}}}
        else {
          goto L65353;}}
      else {
        goto L65353;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_181:
#else
    case 181 : 
#endif
      {
      if ((0 == (3 & (SvalS)))) {
        index_1682X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
        if ((index_1682X < (Snumber_of_event_typesS))) {
          goto L6577;}
        else {
          ps_write_string("trying to unregister invalid external event: ", (stderr));
          ps_write_integer(index_1682X, (stderr));
          { long ignoreXX;
          PS_WRITE_CHAR(10, (stderr), ignoreXX) }
          ps_error("assertion violation", 0);
          goto L6577;}}
      else {push_exception_setupB(5, 1);
        x_1683X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1683X);
        arg0K0 = 1;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_182:
#else
    case 182 : 
#endif
      {
      arg2_1684X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((0 == (3 & arg2_1684X))) {
        option_1685X = PS_SHIFT_RIGHT_INLINE(arg2_1684X, 2);
        other_1686X = SvalS;
        if ((2 == option_1685X)) {
          x_1687X = CHEAP_TIME();
          SvalS = (PS_SHIFT_LEFT_INLINE(x_1687X, 2));
          Scode_pointerS = ((Scode_pointerS) + 1);
          arg3K0 = (Scode_pointerS);
          goto L36237;}
        else {
          if ((0 == option_1685X)) {
            seconds_1688X = s48_run_time(&mseconds_1689X);
            arg0K0 = option_1685X;
            arg0K1 = seconds_1688X;
            arg0K2 = mseconds_1689X;
            goto L63852;}
          else {
            if ((1 == option_1685X)) {
              seconds_1690X = s48_real_time(&mseconds_1691X);
              arg0K0 = option_1685X;
              arg0K1 = seconds_1690X;
              arg0K2 = mseconds_1691X;
              goto L63852;}
            else {
              if ((3 == option_1685X)) {
                seconds_1692X = s48_gc_run_time(&mseconds_1693X);
                arg0K0 = option_1685X;
                arg0K1 = seconds_1692X;
                arg0K2 = mseconds_1693X;
                goto L63852;}
              else {push_exception_setupB(18, 1);
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(option_1685X, 2)));
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) (other_1686X);
                arg0K0 = 2;
                goto L33796;}}}}}
      else {push_exception_setupB(5, 1);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg2_1684X);
        x_1694X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1694X);
        arg0K0 = 2;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_183:
#else
    case 183 : 
#endif
      {
      if ((0 == (3 & (SvalS)))) {
        key_1695X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
        if ((0 == key_1695X)) {
          val_1696X = enter_stringAgc_n(S48_HOST_ARCHITECTURE, (strlen((char *) S48_HOST_ARCHITECTURE)));
          SvalS = val_1696X;
          Scode_pointerS = ((Scode_pointerS) + 1);
          arg3K0 = (Scode_pointerS);
          goto L36237;}
        else {
          if ((1 == key_1695X)) {
            string_1697X = s48_get_os_string_encoding();
            val_1698X = enter_stringAgc_n(string_1697X, (strlen((char *) string_1697X)));
            SvalS = val_1698X;
            Scode_pointerS = ((Scode_pointerS) + 1);
            arg3K0 = (Scode_pointerS);
            goto L36237;}
          else {push_exception_setupB(18, 1);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(key_1695X, 2)));
            arg0K0 = 1;
            goto L33796;}}}
      else {push_exception_setupB(5, 1);
        x_1699X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1699X);
        arg0K0 = 1;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_184:
#else
    case 184 : 
#endif
      {
      arg2_1700X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((0 == (3 & arg2_1700X))) {
        key_1701X = PS_SHIFT_RIGHT_INLINE(arg2_1700X, 2);
        value_1702X = SvalS;
        status_1703X = s48_extended_vm(key_1701X, value_1702X);
        if ((0 == status_1703X)) {
          SvalS = (s48_Sextension_valueS);
          Scode_pointerS = ((Scode_pointerS) + 1);
          arg3K0 = (Scode_pointerS);
          goto L36237;}
        else {
          if ((1 == status_1703X)) {push_exception_setupB(23, 1);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(key_1701X, 2)));
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (value_1702X);
            arg0K0 = 2;
            goto L33796;}
          else {push_exception_setupB(24, 1);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(key_1701X, 2)));
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (value_1702X);
            arg0K0 = 2;
            goto L33796;}}}
      else {push_exception_setupB(5, 1);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg2_1700X);
        x_1704X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1704X);
        arg0K0 = 2;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_185:
#else
    case 185 : 
#endif
      {
      arg2_1705X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      x_1706X = SvalS;
      Senabled_interruptsS = -1;
      if ((0 == ((Spending_interruptsS) & (Senabled_interruptsS)))) {
        s48_Sstack_limitS = (Sreal_stack_limitS);
        if ((s48_Spending_eventsPS)) {
          s48_Sstack_limitS = (((char *) -1));
          goto L68225;}
        else {
          goto L68225;}}
      else {
        s48_Sstack_limitS = (((char *) -1));
        goto L68225;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_186:
#else
    case 186 : 
#endif
      {
      arg2_1707X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((3 == (3 & arg2_1707X))) {
        if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1707X))))), 2))))) {
          obj_1708X = SvalS;
          if ((3 == (3 & obj_1708X))) {
            if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_1708X))))), 2))))) {
              x_1709X = SvalS;
              len_1710X = PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg2_1707X))))), 8);
              if ((len_1710X == (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + x_1709X))))), 8)))) {
                if (((!memcmp((void *)(((char *) (-3 + x_1709X))), (void *)(((char *) (-3 + arg2_1707X))),len_1710X)))) {
                  arg0K0 = 5;
                  goto L55759;}
                else {
                  arg0K0 = 1;
                  goto L55759;}}
              else {
                arg0K0 = 1;
                goto L55759;}}
            else {
              goto L55724;}}
          else {
            goto L55724;}}
        else {
          goto L55724;}}
      else {
        goto L55724;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_187:
#else
    case 187 : 
#endif
      {s48_make_availableAgc((8 + (-8 & (7 + (-4 & (SvalS))))));
      arg2_1711X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((0 == (3 & (SvalS)))) {
        n_1712X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
        if ((3 == (3 & arg2_1711X))) {
          if ((0 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1711X))))), 2))))) {
            goto L54157;}
          else {
            goto L54109;}}
        else {
          goto L54109;}}
      else {push_exception_setupB(5, 1);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg2_1711X);
        x_1713X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1713X);
        arg0K0 = 2;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_188:
#else
    case 188 : 
#endif
      {
      arg2_1714X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      list_1715X = SvalS;
      arg0K0 = list_1715X;
      arg0K1 = list_1715X;
      arg4K2 = 1;
      goto L57125;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_189:
#else
    case 189 : 
#endif
      {
      if ((529 == (SvalS))) {push_exception_setupB(0, 1);
        arg0K0 = 0;
        goto L33796;}
      else {
        Scode_pointerS = ((Scode_pointerS) + 1);
        arg3K0 = (Scode_pointerS);
        goto L36237;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_190:
#else
    case 190 : 
#endif
      {
      arg2_1716X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      x_1717X = not_record_typeP(arg2_1716X);
      if (x_1717X) {
        goto L55570;}
      else {
        x_1718X = not_record_typeP((SvalS));
        if (x_1718X) {
          goto L55570;}
        else {
          x_1719X = SvalS;
          if ((arg2_1716X == x_1719X)) {
            arg0K0 = 5;
            goto L55611;}
          else {
            ec2_1720X = PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + x_1719X))) + 64))), 2);
            if (((PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + arg2_1716X))) + 64))), 2)) < ec2_1720X)) {
              arg0K0 = 1;
              goto L55611;}
            else {
              if (((*((long *) ((((char *) (-3 + arg2_1716X))) + (88 + (PS_SHIFT_LEFT_INLINE(ec2_1720X, 3)))))) == x_1719X)) {
                arg0K0 = 5;
                goto L55611;}
              else {
                arg0K0 = 1;
                goto L55611;}}}}}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_191:
#else
    case 191 : 
#endif
      {
      arg2_1721X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg3_1722X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((0 == (3 & (SvalS)))) {
        index_1723X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
        if ((3 == (3 & arg3_1722X))) {
          if ((9 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg3_1722X))))), 2))))) {
            rt1_1724X = *((long *) (((char *) (-3 + arg3_1722X))));
            if ((rt1_1724X == arg2_1721X)) {
              goto L42527;}
            else {
              ec2_1725X = PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + arg2_1721X))) + 64))), 2);
              if (((PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + rt1_1724X))) + 64))), 2)) < ec2_1725X)) {
                goto L42526;}
              else {
                if (((*((long *) ((((char *) (-3 + rt1_1724X))) + (88 + (PS_SHIFT_LEFT_INLINE(ec2_1725X, 3)))))) == arg2_1721X)) {
                  goto L42527;}
                else {
                  goto L42526;}}}}
          else {
            goto L42526;}}
        else {
          goto L42526;}}
      else {push_exception_setupB(5, 1);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg3_1722X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg2_1721X);
        x_1726X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1726X);
        arg0K0 = 3;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_192:
#else
    case 192 : 
#endif
      {
      arg2_1727X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg3_1728X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg4_1729X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((0 == (3 & arg2_1727X))) {
        index_1730X = PS_SHIFT_RIGHT_INLINE(arg2_1727X, 2);
        value_1731X = SvalS;
        if ((3 == (3 & arg4_1729X))) {
          if ((9 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg4_1729X))))), 2))))) {
            rt1_1732X = *((long *) (((char *) (-3 + arg4_1729X))));
            if ((rt1_1732X == arg3_1728X)) {
              goto L42817;}
            else {
              ec2_1733X = PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + arg3_1728X))) + 64))), 2);
              if (((PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + rt1_1732X))) + 64))), 2)) < ec2_1733X)) {
                goto L42816;}
              else {
                if (((*((long *) ((((char *) (-3 + rt1_1732X))) + (88 + (PS_SHIFT_LEFT_INLINE(ec2_1733X, 3)))))) == arg3_1728X)) {
                  goto L42817;}
                else {
                  goto L42816;}}}}
          else {
            goto L42816;}}
        else {
          goto L42816;}}
      else {push_exception_setupB(5, 1);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg4_1729X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg3_1728X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg2_1727X);
        x_1734X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1734X);
        arg0K0 = 4;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_193:
#else
    case 193 : 
#endif
      {
      arg2_1735X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg3_1736X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg4_1737X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg5_1738X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((0 == (3 & arg5_1738X))) {
        if ((9 == (255 & arg4_1737X))) {
          if ((3 == (3 & arg3_1736X))) {
            if ((17 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg3_1736X))))), 2))))) {
              if ((0 == (3 & (arg2_1735X | (SvalS))))) {
                encoding_1739X = PS_SHIFT_RIGHT_INLINE(arg5_1738X, 2);
                value_1740X = PS_SHIFT_RIGHT_INLINE(arg4_1737X, 8);
                start_1741X = PS_SHIFT_RIGHT_INLINE(arg2_1735X, 2);
                count_1742X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
                if ((3 == (3 & arg3_1736X))) {
                  if ((0 == (128 & (*((long *) (((char *) (-11 + arg3_1736X)))))))) {
                    if ((start_1741X < 0)) {
                      goto L34431;}
                    else {
                      if ((count_1742X < 0)) {
                        goto L34431;}
                      else {
                        if (((PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg3_1736X))))), 8)) < (start_1741X + count_1742X))) {
                          goto L34431;}
                        else {
                          buffer_1743X = (((char *) (-3 + arg3_1736X))) + start_1741X;
                          if ((0 == encoding_1739X)) {
                            if ((count_1742X < 1)) {
                              arg4K0 = 1;
                              arg4K1 = 1;
                              arg4K2 = 1;
                              arg0K3 = 1;
                              goto L34460;}
                            else {
                              if ((value_1740X < 128)) {
                                *((unsigned char *) buffer_1743X) = (unsigned char) (value_1740X);
                                arg4K0 = 1;
                                arg4K1 = 1;
                                arg4K2 = 0;
                                arg0K3 = 1;
                                goto L34460;}
                              else {
                                arg4K0 = 1;
                                arg4K1 = 0;
                                arg4K2 = 0;
                                arg0K3 = 0;
                                goto L34460;}}}
                          else {
                            if ((1 == encoding_1739X)) {
                              if ((count_1742X < 1)) {
                                arg4K0 = 1;
                                arg4K1 = 1;
                                arg4K2 = 1;
                                arg0K3 = 1;
                                goto L34460;}
                              else {
                                if ((value_1740X < 256)) {
                                  *((unsigned char *) buffer_1743X) = (unsigned char) (value_1740X);
                                  arg4K0 = 1;
                                  arg4K1 = 1;
                                  arg4K2 = 0;
                                  arg0K3 = 1;
                                  goto L34460;}
                                else {
                                  arg4K0 = 1;
                                  arg4K1 = 0;
                                  arg4K2 = 0;
                                  arg0K3 = 0;
                                  goto L34460;}}}
                            else {
                              if ((2 == encoding_1739X)) {
                                encoding_okP_1744X = encode_scalar_valueUutf_8(value_1740X, buffer_1743X, count_1742X, &out_of_spaceP_1745X, &count_1746X);
                                arg4K0 = 1;
                                arg4K1 = encoding_okP_1744X;
                                arg4K2 = out_of_spaceP_1745X;
                                arg0K3 = count_1746X;
                                goto L34460;}
                              else {
                                if ((3 == encoding_1739X)) {
                                  encoding_okP_1747X = encode_scalar_valueUutf_16le(value_1740X, buffer_1743X, count_1742X, &out_of_spaceP_1748X, &count_1749X);
                                  arg4K0 = 1;
                                  arg4K1 = encoding_okP_1747X;
                                  arg4K2 = out_of_spaceP_1748X;
                                  arg0K3 = count_1749X;
                                  goto L34460;}
                                else {
                                  if ((4 == encoding_1739X)) {
                                    encoding_okP_1750X = encode_scalar_valueUutf_16be(value_1740X, buffer_1743X, count_1742X, &out_of_spaceP_1751X, &count_1752X);
                                    arg4K0 = 1;
                                    arg4K1 = encoding_okP_1750X;
                                    arg4K2 = out_of_spaceP_1751X;
                                    arg0K3 = count_1752X;
                                    goto L34460;}
                                  else {
                                    if ((5 == encoding_1739X)) {
                                      if ((count_1742X < 4)) {
                                        arg4K0 = 1;
                                        arg4K1 = 1;
                                        arg4K2 = 1;
                                        arg0K3 = 4;
                                        goto L34460;}
                                      else {
                                        *((unsigned char *) buffer_1743X) = (unsigned char) ((255 & value_1740X));
                                        *((unsigned char *) (buffer_1743X + 1)) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE((65280 & value_1740X), 8)));
                                        *((unsigned char *) (buffer_1743X + 2)) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE((16711680 & value_1740X), 16)));
                                        *((unsigned char *) (buffer_1743X + 3)) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE(value_1740X, 24)));
                                        arg4K0 = 1;
                                        arg4K1 = 1;
                                        arg4K2 = 0;
                                        arg0K3 = 4;
                                        goto L34460;}}
                                    else {
                                      if ((6 == encoding_1739X)) {
                                        if ((count_1742X < 4)) {
                                          arg4K0 = 1;
                                          arg4K1 = 1;
                                          arg4K2 = 1;
                                          arg0K3 = 4;
                                          goto L34460;}
                                        else {
                                          *((unsigned char *) buffer_1743X) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE(value_1740X, 24)));
                                          *((unsigned char *) (buffer_1743X + 1)) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE((16711680 & value_1740X), 16)));
                                          *((unsigned char *) (buffer_1743X + 2)) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE((65280 & value_1740X), 8)));
                                          *((unsigned char *) (buffer_1743X + 3)) = (unsigned char) ((255 & value_1740X));
                                          arg4K0 = 1;
                                          arg4K1 = 1;
                                          arg4K2 = 0;
                                          arg0K3 = 4;
                                          goto L34460;}}
                                      else {
                                        arg4K0 = 0;
                                        arg4K1 = 0;
                                        arg4K2 = 0;
                                        arg0K3 = 0;
                                        goto L34460;}}}}}}}}}}}
                  else {
                    goto L34431;}}
                else {
                  goto L34431;}}
              else {
                goto L35283;}}
            else {
              goto L35283;}}
          else {
            goto L35283;}}
        else {
          goto L35283;}}
      else {
        goto L35283;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_194:
#else
    case 194 : 
#endif
      {
      arg2_1753X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg3_1754X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg4_1755X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg5_1756X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((0 == (3 & arg5_1756X))) {
        if ((9 == (255 & arg4_1755X))) {
          if ((3 == (3 & arg3_1754X))) {
            if ((17 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg3_1754X))))), 2))))) {
              if ((0 == (3 & (arg2_1753X | (SvalS))))) {
                encoding_1757X = PS_SHIFT_RIGHT_INLINE(arg5_1756X, 2);
                value_1758X = PS_SHIFT_RIGHT_INLINE(arg4_1755X, 8);
                start_1759X = PS_SHIFT_RIGHT_INLINE(arg2_1753X, 2);
                count_1760X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
                if ((3 == (3 & arg3_1754X))) {
                  if ((0 == (128 & (*((long *) (((char *) (-11 + arg3_1754X)))))))) {
                    if ((start_1759X < 0)) {
                      goto L54312;}
                    else {
                      if ((count_1760X < 0)) {
                        goto L54312;}
                      else {
                        if (((PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg3_1754X))))), 8)) < (start_1759X + count_1760X))) {
                          goto L54312;}
                        else {
                          buffer_1761X = (((char *) (-3 + arg3_1754X))) + start_1759X;
                          if ((0 == encoding_1757X)) {
                            if ((count_1760X < 1)) {
                              goto L54348;}
                            else {
                              if ((value_1758X < 128)) {
                                *((unsigned char *) buffer_1761X) = (unsigned char) (value_1758X);
                                goto L54348;}
                              else {
                                goto L54348;}}}
                          else {
                            if ((1 == encoding_1757X)) {
                              if ((count_1760X < 1)) {
                                goto L54348;}
                              else {
                                if ((value_1758X < 256)) {
                                  *((unsigned char *) buffer_1761X) = (unsigned char) (value_1758X);
                                  goto L54348;}
                                else {
                                  goto L54348;}}}
                            else {
                              if ((2 == encoding_1757X)) {encode_scalar_valueUutf_8(value_1758X, buffer_1761X, count_1760X, &out_of_spaceP_1762X, &count_1763X);
                                goto L54348;}
                              else {
                                if ((3 == encoding_1757X)) {encode_scalar_valueUutf_16le(value_1758X, buffer_1761X, count_1760X, &out_of_spaceP_1764X, &count_1765X);
                                  goto L54348;}
                                else {
                                  if ((4 == encoding_1757X)) {encode_scalar_valueUutf_16be(value_1758X, buffer_1761X, count_1760X, &out_of_spaceP_1766X, &count_1767X);
                                    goto L54348;}
                                  else {
                                    if ((5 == encoding_1757X)) {
                                      if ((count_1760X < 4)) {
                                        goto L54348;}
                                      else {
                                        *((unsigned char *) buffer_1761X) = (unsigned char) ((255 & value_1758X));
                                        *((unsigned char *) (buffer_1761X + 1)) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE((65280 & value_1758X), 8)));
                                        *((unsigned char *) (buffer_1761X + 2)) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE((16711680 & value_1758X), 16)));
                                        *((unsigned char *) (buffer_1761X + 3)) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE(value_1758X, 24)));
                                        goto L54348;}}
                                    else {
                                      if ((6 == encoding_1757X)) {
                                        if ((count_1760X < 4)) {
                                          goto L54348;}
                                        else {
                                          *((unsigned char *) buffer_1761X) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE(value_1758X, 24)));
                                          *((unsigned char *) (buffer_1761X + 1)) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE((16711680 & value_1758X), 16)));
                                          *((unsigned char *) (buffer_1761X + 2)) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE((65280 & value_1758X), 8)));
                                          *((unsigned char *) (buffer_1761X + 3)) = (unsigned char) ((255 & value_1758X));
                                          goto L54348;}}
                                      else {push_exception_setupB(18, 1);
                                        SstackS = ((SstackS) + -8);
                                        *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(encoding_1757X, 2)));
                                        arg0K0 = 1;
                                        goto L33796;}}}}}}}}}}}
                  else {
                    goto L54312;}}
                else {
                  goto L54312;}}
              else {
                goto L62046;}}
            else {
              goto L62046;}}
          else {
            goto L62046;}}
        else {
          goto L62046;}}
      else {
        goto L62046;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_195:
#else
    case 195 : 
#endif
      {
      arg2_1768X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg3_1769X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg4_1770X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((0 == (3 & arg4_1770X))) {
        if ((3 == (3 & arg3_1769X))) {
          if ((17 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg3_1769X))))), 2))))) {
            if ((0 == (3 & (arg2_1768X | (SvalS))))) {
              encoding_1771X = PS_SHIFT_RIGHT_INLINE(arg4_1770X, 2);
              start_1772X = PS_SHIFT_RIGHT_INLINE(arg2_1768X, 2);
              count_1773X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
              if ((start_1772X < 0)) {
                goto L34780;}
              else {
                if ((count_1773X < 0)) {
                  goto L34780;}
                else {
                  if (((PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg3_1769X))))), 8)) < (start_1772X + count_1773X))) {
                    goto L34780;}
                  else {
                    buffer_1774X = (((char *) (-3 + arg3_1769X))) + start_1772X;
                    if ((0 == encoding_1771X)) {
                      arg4K0 = 1;
                      arg4K1 = 1;
                      arg4K2 = 0;
                      arg0K3 = (*((unsigned char *) buffer_1774X));
                      arg0K4 = 1;
                      goto L34806;}
                    else {
                      if ((1 == encoding_1771X)) {
                        arg4K0 = 1;
                        arg4K1 = 1;
                        arg4K2 = 0;
                        arg0K3 = (*((unsigned char *) buffer_1774X));
                        arg0K4 = 1;
                        goto L34806;}
                      else {
                        if ((2 == encoding_1771X)) {
                          okP_1775X = decode_scalar_valueUutf_8(buffer_1774X, count_1773X, &incompleteP_1776X, &value_1777X, &count_1778X);
                          arg4K0 = 1;
                          arg4K1 = okP_1775X;
                          arg4K2 = incompleteP_1776X;
                          arg0K3 = value_1777X;
                          arg0K4 = count_1778X;
                          goto L34806;}
                        else {
                          if ((3 == encoding_1771X)) {
                            okP_1779X = decode_scalar_valueUutf_16le(buffer_1774X, count_1773X, &incompleteP_1780X, &value_1781X, &count_1782X);
                            arg4K0 = 1;
                            arg4K1 = okP_1779X;
                            arg4K2 = incompleteP_1780X;
                            arg0K3 = value_1781X;
                            arg0K4 = count_1782X;
                            goto L34806;}
                          else {
                            if ((4 == encoding_1771X)) {
                              okP_1783X = decode_scalar_valueUutf_16be(buffer_1774X, count_1773X, &incompleteP_1784X, &value_1785X, &count_1786X);
                              arg4K0 = 1;
                              arg4K1 = okP_1783X;
                              arg4K2 = incompleteP_1784X;
                              arg0K3 = value_1785X;
                              arg0K4 = count_1786X;
                              goto L34806;}
                            else {
                              if ((5 == encoding_1771X)) {
                                if ((count_1773X < 4)) {
                                  arg4K0 = 1;
                                  arg4K1 = 1;
                                  arg4K2 = 1;
                                  arg0K3 = 0;
                                  arg0K4 = 4;
                                  goto L34806;}
                                else {
                                  code_point_1787X = (((*((unsigned char *) buffer_1774X)) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_1774X + 1))), 8))) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_1774X + 2))), 16))) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_1774X + 3))), 24));
                                  if ((code_point_1787X < 0)) {
                                    arg4K0 = 1;
                                    arg4K1 = 0;
                                    arg4K2 = 0;
                                    arg0K3 = 0;
                                    arg0K4 = 0;
                                    goto L34806;}
                                  else {
                                    if ((55295 < code_point_1787X)) {
                                      if ((code_point_1787X < 57344)) {
                                        arg4K0 = 1;
                                        arg4K1 = 0;
                                        arg4K2 = 0;
                                        arg0K3 = 0;
                                        arg0K4 = 0;
                                        goto L34806;}
                                      else {
                                        if ((1114111 < code_point_1787X)) {
                                          arg4K0 = 1;
                                          arg4K1 = 0;
                                          arg4K2 = 0;
                                          arg0K3 = 0;
                                          arg0K4 = 0;
                                          goto L34806;}
                                        else {
                                          arg4K0 = 1;
                                          arg4K1 = 1;
                                          arg4K2 = 0;
                                          arg0K3 = code_point_1787X;
                                          arg0K4 = 4;
                                          goto L34806;}}}
                                    else {
                                      arg4K0 = 1;
                                      arg4K1 = 1;
                                      arg4K2 = 0;
                                      arg0K3 = code_point_1787X;
                                      arg0K4 = 4;
                                      goto L34806;}}}}
                              else {
                                if ((6 == encoding_1771X)) {
                                  if ((count_1773X < 4)) {
                                    arg4K0 = 1;
                                    arg4K1 = 1;
                                    arg4K2 = 1;
                                    arg0K3 = 0;
                                    arg0K4 = 4;
                                    goto L34806;}
                                  else {
                                    code_point_1788X = (((PS_SHIFT_LEFT_INLINE((*((unsigned char *) buffer_1774X)), 24)) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_1774X + 1))), 16))) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_1774X + 2))), 8))) + (*((unsigned char *) (buffer_1774X + 3)));
                                    if ((code_point_1788X < 0)) {
                                      arg4K0 = 1;
                                      arg4K1 = 0;
                                      arg4K2 = 0;
                                      arg0K3 = 0;
                                      arg0K4 = 0;
                                      goto L34806;}
                                    else {
                                      if ((55295 < code_point_1788X)) {
                                        if ((code_point_1788X < 57344)) {
                                          arg4K0 = 1;
                                          arg4K1 = 0;
                                          arg4K2 = 0;
                                          arg0K3 = 0;
                                          arg0K4 = 0;
                                          goto L34806;}
                                        else {
                                          if ((1114111 < code_point_1788X)) {
                                            arg4K0 = 1;
                                            arg4K1 = 0;
                                            arg4K2 = 0;
                                            arg0K3 = 0;
                                            arg0K4 = 0;
                                            goto L34806;}
                                          else {
                                            arg4K0 = 1;
                                            arg4K1 = 1;
                                            arg4K2 = 0;
                                            arg0K3 = code_point_1788X;
                                            arg0K4 = 4;
                                            goto L34806;}}}
                                      else {
                                        arg4K0 = 1;
                                        arg4K1 = 1;
                                        arg4K2 = 0;
                                        arg0K3 = code_point_1788X;
                                        arg0K4 = 4;
                                        goto L34806;}}}}
                                else {
                                  arg4K0 = 0;
                                  arg4K1 = 0;
                                  arg4K2 = 0;
                                  arg0K3 = 0;
                                  arg0K4 = 0;
                                  goto L34806;}}}}}}}}}}}
            else {
              goto L35479;}}
          else {
            goto L35479;}}
        else {
          goto L35479;}}
      else {
        goto L35479;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_196:
#else
    case 196 : 
#endif
      {
      arg2_1789X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg3_1790X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg4_1791X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      if ((0 == (3 & arg4_1791X))) {
        if ((3 == (3 & arg3_1790X))) {
          if ((17 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg3_1790X))))), 2))))) {
            if ((0 == (3 & (arg2_1789X | (SvalS))))) {
              encoding_1792X = PS_SHIFT_RIGHT_INLINE(arg4_1791X, 2);
              start_1793X = PS_SHIFT_RIGHT_INLINE(arg2_1789X, 2);
              count_1794X = PS_SHIFT_RIGHT_INLINE((SvalS), 2);
              if ((start_1793X < 0)) {
                goto L54766;}
              else {
                if ((count_1794X < 0)) {
                  goto L54766;}
                else {
                  if (((PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg3_1790X))))), 8)) < (start_1793X + count_1794X))) {
                    goto L54766;}
                  else {
                    buffer_1795X = (((char *) (-3 + arg3_1790X))) + start_1793X;
                    if ((0 == encoding_1792X)) {
                      goto L54919;}
                    else {
                      if ((1 == encoding_1792X)) {
                        goto L54919;}
                      else {
                        if ((2 == encoding_1792X)) {decode_scalar_valueUutf_8(buffer_1795X, count_1794X, &incompleteP_1796X, &value_1797X, &count_1798X);
                          goto L54919;}
                        else {
                          if ((3 == encoding_1792X)) {decode_scalar_valueUutf_16le(buffer_1795X, count_1794X, &incompleteP_1799X, &value_1800X, &count_1801X);
                            goto L54919;}
                          else {
                            if ((4 == encoding_1792X)) {decode_scalar_valueUutf_16be(buffer_1795X, count_1794X, &incompleteP_1802X, &value_1803X, &count_1804X);
                              goto L54919;}
                            else {
                              if ((5 == encoding_1792X)) {
                                if ((count_1794X < 4)) {
                                  goto L54919;}
                                else {
                                  code_point_1805X = (((*((unsigned char *) buffer_1795X)) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_1795X + 1))), 8))) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_1795X + 2))), 16))) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_1795X + 3))), 24));
                                  if ((code_point_1805X < 0)) {
                                    goto L54919;}
                                  else {
                                    if ((55295 < code_point_1805X)) {
                                      if ((code_point_1805X < 57344)) {
                                        goto L54919;}
                                      else {
                                        if ((1114111 < code_point_1805X)) {
                                          goto L54919;}
                                        else {
                                          goto L54919;}}}
                                    else {
                                      goto L54919;}}}}
                              else {
                                if ((6 == encoding_1792X)) {
                                  if ((count_1794X < 4)) {
                                    goto L54919;}
                                  else {
                                    code_point_1806X = (((PS_SHIFT_LEFT_INLINE((*((unsigned char *) buffer_1795X)), 24)) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_1795X + 1))), 16))) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_1795X + 2))), 8))) + (*((unsigned char *) (buffer_1795X + 3)));
                                    if ((code_point_1806X < 0)) {
                                      goto L54919;}
                                    else {
                                      if ((55295 < code_point_1806X)) {
                                        if ((code_point_1806X < 57344)) {
                                          goto L54919;}
                                        else {
                                          if ((1114111 < code_point_1806X)) {
                                            goto L54919;}
                                          else {
                                            goto L54919;}}}
                                      else {
                                        goto L54919;}}}}
                                else {push_exception_setupB(18, 1);
                                  SstackS = ((SstackS) + -8);
                                  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(encoding_1792X, 2)));
                                  arg0K0 = 1;
                                  goto L33796;}}}}}}}}}}}
            else {
              goto L62242;}}
          else {
            goto L62242;}}
        else {
          goto L62242;}}
      else {
        goto L62242;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_197:
#else
    case 197 : 
#endif
      {
      v_1807X = *((unsigned char *) ((Scode_pointerS) + 1));
      if ((0 == v_1807X)) {
        arg0K0 = (SvalS);
        goto L43098;}
      else {
        merged_arg0K0 = 0;
#ifdef USE_DIRECT_THREADING
        get_current_port_return_address = &&get_current_port_return_0;
#else
        get_current_port_return_tag = 0;
#endif
        goto get_current_port;
       get_current_port_return_0:
        v_1808X = get_current_port0_return_value;
        arg0K0 = v_1808X;
        goto L43098;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_198:
#else
    case 198 : 
#endif
      {
      v_1809X = *((unsigned char *) ((Scode_pointerS) + 1));
      if ((0 == v_1809X)) {
        arg0K0 = (SvalS);
        goto L43300;}
      else {
        merged_arg0K0 = 0;
#ifdef USE_DIRECT_THREADING
        get_current_port_return_address = &&get_current_port_return_1;
#else
        get_current_port_return_tag = 1;
#endif
        goto get_current_port;
       get_current_port_return_1:
        v_1810X = get_current_port0_return_value;
        arg0K0 = v_1810X;
        goto L43300;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_199:
#else
    case 199 : 
#endif
      {
      v_1811X = *((unsigned char *) ((Scode_pointerS) + 1));
      if ((0 == v_1811X)) {
        v_1812X = *((long *) (SstackS));
        SstackS = ((SstackS) + 8);
        arg0K0 = v_1812X;
        arg0K1 = (SvalS);
        goto L43495;}
      else {
        merged_arg0K0 = 4;
#ifdef USE_DIRECT_THREADING
        get_current_port_return_address = &&get_current_port_return_2;
#else
        get_current_port_return_tag = 2;
#endif
        goto get_current_port;
       get_current_port_return_2:
        v_1813X = get_current_port0_return_value;
        arg0K0 = (SvalS);
        arg0K1 = v_1813X;
        goto L43495;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_200:
#else
    case 200 : 
#endif
      {
      v_1814X = *((unsigned char *) ((Scode_pointerS) + 1));
      if ((0 == v_1814X)) {
        arg0K0 = (SvalS);
        goto L43764;}
      else {
        merged_arg0K0 = 0;
#ifdef USE_DIRECT_THREADING
        get_current_port_return_address = &&get_current_port_return_3;
#else
        get_current_port_return_tag = 3;
#endif
        goto get_current_port;
       get_current_port_return_3:
        v_1815X = get_current_port0_return_value;
        arg0K0 = v_1815X;
        goto L43764;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_201:
#else
    case 201 : 
#endif
      {
      v_1816X = *((unsigned char *) ((Scode_pointerS) + 1));
      if ((0 == v_1816X)) {
        arg0K0 = (SvalS);
        goto L44412;}
      else {
        merged_arg0K0 = 0;
#ifdef USE_DIRECT_THREADING
        get_current_port_return_address = &&get_current_port_return_4;
#else
        get_current_port_return_tag = 4;
#endif
        goto get_current_port;
       get_current_port_return_4:
        v_1817X = get_current_port0_return_value;
        arg0K0 = v_1817X;
        goto L44412;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_202:
#else
    case 202 : 
#endif
      {
      v_1818X = *((unsigned char *) ((Scode_pointerS) + 1));
      if ((0 == v_1818X)) {
        v_1819X = *((long *) (SstackS));
        SstackS = ((SstackS) + 8);
        arg0K0 = v_1819X;
        arg0K1 = (SvalS);
        goto L44981;}
      else {
        merged_arg0K0 = 4;
#ifdef USE_DIRECT_THREADING
        get_current_port_return_address = &&get_current_port_return_5;
#else
        get_current_port_return_tag = 5;
#endif
        goto get_current_port;
       get_current_port_return_5:
        v_1820X = get_current_port0_return_value;
        arg0K0 = (SvalS);
        arg0K1 = v_1820X;
        goto L44981;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_203:
#else
    case 203 : 
#endif
      {
      if ((0 == (3 & (SvalS)))) {
        raw_1821X = ps_error_string((PS_SHIFT_RIGHT_INLINE((SvalS), 2)));
        len_1822X = 1 + (strlen((char *) raw_1821X));
        addr_1823X = s48_allocate_untracedAgc((8 + len_1822X));
        if ((addr_1823X == NULL)) {
          arg0K0 = 1;
          goto L55249;}
        else {
          *((long *) addr_1823X) = (long) ((70 + (PS_SHIFT_LEFT_INLINE(len_1822X, 8))));
          arg0K0 = (3 + (((long) (addr_1823X + 8))));
          goto L55249;}}
      else {push_exception_setupB(5, 1);
        x_1824X = SvalS;
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (x_1824X);
        arg0K0 = 1;
        goto L33796;}}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifdef USE_DIRECT_THREADING
Jlabel36237_204:
#else
    case 204 : 
#endif
      {
      x_1825X = SvalS;
      out_1826X = stderr;
      arg0K0 = x_1825X;
      goto L57378;}
#ifndef USE_DIRECT_THREADING
      break;
#endif

#ifndef USE_DIRECT_THREADING
  }
#endif
}
 L32871: {
  i_1827X = arg0K0;
  m_1828X = arg0K1;
  if ((0 == (n_1218X & m_1828X))) {
    arg0K0 = (1 + i_1827X);
    arg0K1 = (PS_SHIFT_LEFT_INLINE(m_1828X, 1));
    goto L32871;}
  else {
    Spending_interruptsS = ((Spending_interruptsS) & (~ m_1828X));
    handlers_1829X = SHARED_REF((Sinterrupt_handlersS));
    if ((i_1827X == 0)) {
      x_1830X = Sinterrupted_templateS;
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_1830X);
      Sinterrupted_templateS = 1;
      n_1831X = Senabled_interruptsS;
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(n_1831X, 2)));
      arg0K0 = 2;
      goto L32828;}
    else {
      if ((i_1827X == 3)) {
        goto L17869;}
      else {
        if ((i_1827X == 2)) {
          goto L17869;}
        else {
          if ((i_1827X == 4)) {
            channel_1832X = Spending_channels_headS;
            next_1833X = *((long *) ((((char *) (-3 + channel_1832X))) + 32));
            Spending_channels_headS = next_1833X;
            addr_1834X = (((char *) (-3 + channel_1832X))) + 32;S48_WRITE_BARRIER(channel_1832X, addr_1834X, 1);
            *((long *) addr_1834X) = (long) (1);
            if ((1 == next_1833X)) {
              Spending_channels_tailS = 1;
              arg0K0 = channel_1832X;
              goto L17886;}
            else {
              arg0K0 = channel_1832X;
              goto L17886;}}
          else {
            if ((i_1827X == 5)) {
              v_1835X = (Sos_signal_ring_startS) == (Sos_signal_ring_endS);
              if (v_1835X) {
                ps_error("This cannot happen: OS signal ring empty", 0);
                goto L18107;}
              else {
                goto L18107;}}
            else {
              if ((i_1827X == 6)) {
                uid_1836X = s48_dequeue_external_event(&still_readyP_1837X);
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(uid_1836X, 2)));
                if (still_readyP_1837X) {
                  Spending_interruptsS = (64 | (Spending_interruptsS));
                  if ((0 == ((Spending_interruptsS) & (Senabled_interruptsS)))) {
                    s48_Sstack_limitS = (Sreal_stack_limitS);
                    if ((s48_Spending_eventsPS)) {
                      s48_Sstack_limitS = (((char *) -1));
                      goto L17958;}
                    else {
                      goto L17958;}}
                  else {
                    s48_Sstack_limitS = (((char *) -1));
                    goto L17958;}}
                else {
                  goto L17958;}}
              else {
                n_1838X = Senabled_interruptsS;
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(n_1838X, 2)));
                arg0K0 = 1;
                goto L32828;}}}}}}}}
 L65712: {
  tag_1839X = arg0K0;
  if ((tag_1839X == 0)) {
    arg0K0 = (s48_Snative_protocolS);
    arg0K1 = 25;
    arg0K2 = 0;
    goto L33224;}
  else {
    if ((tag_1839X == 1)) {
      stack_arg_count_1840X = s48_Snative_protocolS;
      obj_1841X = SvalS;
      if ((3 == (3 & obj_1841X))) {
        if ((3 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_1841X))))), 2))))) {
          arg0K0 = stack_arg_count_1840X;
          arg0K1 = 25;
          arg0K2 = 0;
          arg0K3 = -1;
          goto L66500;}
        else {
          arg0K0 = 3;
          arg0K1 = stack_arg_count_1840X;
          arg0K2 = 25;
          arg0K3 = 0;
          goto L33486;}}
      else {
        arg0K0 = 3;
        arg0K1 = stack_arg_count_1840X;
        arg0K2 = 25;
        arg0K3 = 0;
        goto L33486;}}
    else {
      if ((tag_1839X == 2)) {
        template_1842X = *((long *) (SstackS));
        SstackS = ((SstackS) + 8);
        return_address_1843X = *((long *) (SstackS));
        SstackS = ((SstackS) + 8);
#ifdef USE_DIRECT_THREADING
        pending_interruptP_return_address = &&pending_interruptP_return_4;
#else
        pending_interruptP_return_tag = 4;
#endif
        goto pending_interruptP;
       pending_interruptP_return_4:
        v_1844X = pending_interruptP0_return_value;
        if (v_1844X) {
          x_1845X = SvalS;
          SstackS = ((SstackS) + -8);
          *((long *) (SstackS)) = (long) (x_1845X);
          SstackS = ((SstackS) + -8);
          *((long *) (SstackS)) = (long) (template_1842X);
          SstackS = ((SstackS) + -8);
          *((long *) (SstackS)) = (long) (return_address_1843X);
          x_1846X = *((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24));
          SstackS = ((SstackS) + -8);
          *((long *) (SstackS)) = (long) (x_1846X);
          x_1847X = Scurrent_threadS;
          addr_1848X = (((char *) (-3 + x_1847X))) + 24;S48_WRITE_BARRIER(x_1847X, addr_1848X, 1);
          *((long *) addr_1848X) = (long) (1);
          n_1849X = Senabled_interruptsS;
          SstackS = ((SstackS) + -8);
          *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(n_1849X, 2)));
          code_1850X = Snative_poll_return_codeS;
          v_1851X = PS_SHIFT_RIGHT_INLINE(((ScontS) - (SstackS)), 3);
          SstackS = ((SstackS) + -8);
          *((long *) (SstackS)) = (long) ((4 + (PS_SHIFT_LEFT_INLINE(v_1851X, 2))));
          SstackS = ((SstackS) + -8);
          *((long *) (SstackS)) = (long) ((((long) ((((char *) (-3 + code_1850X))) + 13))));
          ScontS = (SstackS);
          goto L32818;}
        else {
          v_1852X = s48_jump_to_native_address(return_address_1843X, template_1842X);
          arg0K0 = v_1852X;
          goto L65712;}}
      else {
        if ((tag_1839X == 3)) {
          ps_error("unexpected native return value", 1, tag_1839X);
          arg0K0 = v_1853X;
          goto L70968;}
        else {
          if ((tag_1839X == 4)) {
            arg3K0 = (Scode_pointerS);
            goto L36237;}
          else {
            if ((tag_1839X == 5)) {
              maybe_cont_1854X = *((long *) (SstackS));
              SstackS = ((SstackS) + 8);
              stack_nargs_1855X = s48_Snative_protocolS;
              list_args_1856X = *((long *) (SstackS));
              SstackS = ((SstackS) + 8);
              merged_arg0K0 = list_args_1856X;
#ifdef USE_DIRECT_THREADING
              okay_argument_list_return_address = &&okay_argument_list_return_1;
#else
              okay_argument_list_return_tag = 1;
#endif
              goto okay_argument_list;
             okay_argument_list_return_1:
              okayP_1857X = okay_argument_list0_return_value;
              length_1858X = okay_argument_list1_return_value;
              if (okayP_1857X) {
                if ((0 == maybe_cont_1854X)) {
                  merged_arg0K0 = stack_nargs_1855X;
#ifdef USE_DIRECT_THREADING
                  move_args_above_contB_return_address = &&move_args_above_contB_return_5;
#else
                  move_args_above_contB_return_tag = 5;
#endif
                  goto move_args_above_contB;
                 move_args_above_contB_return_5:
                  arg0K0 = stack_nargs_1855X;
                  arg0K1 = list_args_1856X;
                  arg0K2 = length_1858X;
                  goto L65449;}
                else {
                  ScontS = ((SstackS) + (PS_SHIFT_LEFT_INLINE(stack_nargs_1855X, 3)));
                  *((long *) (ScontS)) = (long) ((((long) (((char *) maybe_cont_1854X)))));
                  arg0K0 = stack_nargs_1855X;
                  arg0K1 = list_args_1856X;
                  arg0K2 = length_1858X;
                  goto L65449;}}
              else {
                merged_arg0K0 = list_args_1856X;
                merged_arg0K1 = stack_nargs_1855X;
#ifdef USE_DIRECT_THREADING
                pop_args_GlistSAgc_return_address = &&pop_args_GlistSAgc_return_2;
#else
                pop_args_GlistSAgc_return_tag = 2;
#endif
                goto pop_args_GlistSAgc;
               pop_args_GlistSAgc_return_2:
                args_1859X = pop_args_GlistSAgc0_return_value;push_exception_setupB(5, 0);
                x_1860X = SvalS;
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) (x_1860X);
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) (args_1859X);
                arg0K0 = 2;
                goto L33796;}}
            else {
              if ((tag_1839X == 6)) {push_exception_setupB(16, 1);
                x_1861X = SvalS;
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) (x_1861X);
                arg0K0 = 1;
                goto L33796;}
              else {
                ps_error("unexpected native return value", 1, tag_1839X);
                arg0K0 = v_1862X;
                goto L70968;}}}}}}}}
 L36699: {
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L14603: {
  new_env_1863X = arg0K0;
  i_1864X = arg0K1;
  offset_1865X = arg0K2;
  total_count_1866X = arg0K3;
  arg0K0 = (*((unsigned char *) ((Scode_pointerS) + (1 + offset_1865X))));
  arg0K1 = i_1864X;
  arg0K2 = (1 + offset_1865X);
  goto L14609;}
 L25059: {
  count_1867X = arg0K0;
  i_1868X = arg0K1;
  offset_1869X = arg0K2;
  if ((0 == count_1867X)) {
    arg0K0 = new_env_1248X;
    arg0K1 = i_1868X;
    arg0K2 = offset_1869X;
    arg0K3 = total_count_1244X;
    goto L14603;}
  else {
    a_1870X = *((long *) ((((char *) (-3 + template_1249X))) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + (1 + offset_1869X)))), 3))));
    addr_1871X = s48_allocate_small(24);
    *((long *) addr_1871X) = (long) (4110);
    x_1872X = 3 + (((long) (addr_1871X + 8)));
    *((long *) (((char *) (-3 + x_1872X)))) = (long) (a_1870X);
    *((long *) ((((char *) (-3 + x_1872X))) + 8)) = (long) (new_env_1248X);
    addr_1873X = (((char *) (-3 + new_env_1248X))) + (PS_SHIFT_LEFT_INLINE(i_1868X, 3));S48_WRITE_BARRIER(new_env_1248X, addr_1873X, x_1872X);
    *((long *) addr_1873X) = (long) (x_1872X);
    arg0K0 = (-1 + count_1867X);
    arg0K1 = (1 + i_1868X);
    arg0K2 = (1 + offset_1869X);
    goto L25059;}}
 L15398: {
  new_env_1874X = arg0K0;
  i_1875X = arg0K1;
  offset_1876X = arg0K2;
  total_count_1877X = arg0K3;
  arg0K0 = ((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + (1 + offset_1876X)))), 8)) + (*((unsigned char *) ((Scode_pointerS) + (2 + offset_1876X)))));
  arg0K1 = i_1875X;
  arg0K2 = (2 + offset_1876X);
  goto L15404;}
 L25135: {
  count_1878X = arg0K0;
  i_1879X = arg0K1;
  offset_1880X = arg0K2;
  if ((0 == count_1878X)) {
    arg0K0 = new_env_1254X;
    arg0K1 = i_1879X;
    arg0K2 = offset_1880X;
    arg0K3 = total_count_1250X;
    goto L15398;}
  else {
    a_1881X = *((long *) ((((char *) (-3 + template_1255X))) + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + (1 + offset_1880X)))), 8)) + (*((unsigned char *) ((Scode_pointerS) + (2 + offset_1880X))))), 3))));
    addr_1882X = s48_allocate_small(24);
    *((long *) addr_1882X) = (long) (4110);
    x_1883X = 3 + (((long) (addr_1882X + 8)));
    *((long *) (((char *) (-3 + x_1883X)))) = (long) (a_1881X);
    *((long *) ((((char *) (-3 + x_1883X))) + 8)) = (long) (new_env_1254X);
    addr_1884X = (((char *) (-3 + new_env_1254X))) + (PS_SHIFT_LEFT_INLINE(i_1879X, 3));S48_WRITE_BARRIER(new_env_1254X, addr_1884X, x_1883X);
    *((long *) addr_1884X) = (long) (x_1883X);
    arg0K0 = (-1 + count_1878X);
    arg0K1 = (1 + i_1879X);
    arg0K2 = (2 + offset_1880X);
    goto L25135;}}
 L38888: {
  i_1885X = arg0K0;
  if ((0 == i_1885X)) {
    SvalS = closure_1266X;
    Scode_pointerS = ((Scode_pointerS) + 3);
    arg3K0 = (Scode_pointerS);
    goto L36237;}
  else {
    value_1886X = *((long *) (SstackS));
    SstackS = ((SstackS) + 8);
    *((long *) ((((char *) (-3 + closure_1266X))) + (PS_SHIFT_LEFT_INLINE(i_1885X, 3)))) = (long) (value_1886X);
    arg0K0 = (-1 + i_1885X);
    goto L38888;}}
 L67265: {
  n_1887X = arg0K0;
  if ((0 == n_1887X)) {
    Scode_pointerS = ((Scode_pointerS) + 3);
    arg3K0 = (Scode_pointerS);
    goto L36237;}
  else {
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (1);
    arg0K0 = (-1 + n_1887X);
    goto L67265;}}
 L38222: {
  move_1888X = arg0K0;
  if ((move_1888X == n_moves_1274X)) {
    value_1889X = *((long *) (SstackS));
    SstackS = ((SstackS) + 8);
    SvalS = value_1889X;
    Scode_pointerS = ((Scode_pointerS) + (2 + (PS_SHIFT_LEFT_INLINE(n_moves_1274X, 1))));
    arg3K0 = (Scode_pointerS);
    goto L36237;}
  else {
    index_1890X = 1 + (PS_SHIFT_LEFT_INLINE(move_1888X, 1));
    *((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + (2 + index_1890X)))), 3)))) = (long) ((*((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + (1 + index_1890X)))), 3))))));
    arg0K0 = (1 + move_1888X);
    goto L38222;}}
 L38139: {
  move_1891X = arg0K0;
  if ((move_1891X == n_moves_1276X)) {
    value_1892X = *((long *) (SstackS));
    SstackS = ((SstackS) + 8);
    SvalS = value_1892X;
    Scode_pointerS = ((Scode_pointerS) + (3 + (PS_SHIFT_LEFT_INLINE(n_moves_1276X, 2))));
    arg3K0 = (Scode_pointerS);
    goto L36237;}
  else {
    index_1893X = 2 + (PS_SHIFT_LEFT_INLINE(move_1891X, 2));
    value_1894X = *((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + (1 + index_1893X)))), 8)) + (*((unsigned char *) ((Scode_pointerS) + (2 + index_1893X))))), 3))));
    index_1895X = 2 + index_1893X;
    *((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + (1 + index_1895X)))), 8)) + (*((unsigned char *) ((Scode_pointerS) + (2 + index_1895X))))), 3)))) = (long) (value_1894X);
    arg0K0 = (1 + move_1891X);
    goto L38139;}}
 L31400: {
  cont_1896X = arg0K0;
  SstackS = (ScontS);
  arg3K0 = ((SstackS) + -8);
  arg3K1 = (top_1278X + (-8 + (PS_SHIFT_LEFT_INLINE(arg_count_1277X, 3))));
  goto L31426;}
 L66427: {
  stack_arg_count_1897X = arg0K0;
  obj_1898X = SvalS;
  if ((3 == (3 & obj_1898X))) {
    if ((3 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_1898X))))), 2))))) {
      template_1899X = *((long *) (((char *) (-3 + (SvalS)))));
      code_1900X = *((long *) (((char *) (-3 + template_1899X))));
      protocol_1901X = *((unsigned char *) ((((char *) (-3 + code_1900X))) + 1));
      if ((protocol_1901X == stack_arg_count_1897X)) {
        arg0K0 = code_1900X;
        arg0K1 = 2;
        arg0K2 = 3;
        arg0K3 = template_1899X;
        goto L32468;}
      else {
        if (((127 & protocol_1901X) == stack_arg_count_1897X)) {
          if (((SstackS) < (s48_Sstack_limitS))) {
            interruptP_1902X = (s48_Sstack_limitS) == (((char *) -1));
            s48_Sstack_limitS = (Sreal_stack_limitS);
            if (((SstackS) < (Sreal_stack_limitS))) {s48_copy_stack_into_heap();
              if (((SstackS) < (Sreal_stack_limitS))) {
                ps_error("VM's stack is too small (how can this happen?)", 0);
                if (interruptP_1902X) {
                  goto L65913;}
                else {
                  goto L65920;}}
              else {
                if (interruptP_1902X) {
                  goto L65913;}
                else {
                  goto L65920;}}}
            else {
              if (interruptP_1902X) {
                goto L65913;}
              else {
                goto L65920;}}}
          else {
            goto L65920;}}
        else {
          arg0K0 = stack_arg_count_1897X;
          arg0K1 = 25;
          arg0K2 = 0;
          arg0K3 = -1;
          goto L66500;}}}
    else {
      arg0K0 = 3;
      arg0K1 = stack_arg_count_1897X;
      arg0K2 = 25;
      arg0K3 = 0;
      goto L33486;}}
  else {
    arg0K0 = 3;
    arg0K1 = stack_arg_count_1897X;
    arg0K2 = 25;
    arg0K3 = 0;
    goto L33486;}}
 L33599: {
  obj_1903X = SvalS;
  if ((3 == (3 & obj_1903X))) {
    if ((3 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_1903X))))), 2))))) {
      arg0K0 = stack_arg_count_1283X;
      arg0K1 = 25;
      arg0K2 = 0;
      arg0K3 = -1;
      goto L66500;}
    else {
      arg0K0 = 3;
      arg0K1 = stack_arg_count_1283X;
      arg0K2 = 25;
      arg0K3 = 0;
      goto L33486;}}
  else {
    arg0K0 = 3;
    arg0K1 = stack_arg_count_1283X;
    arg0K2 = 25;
    arg0K3 = 0;
    goto L33486;}}
 L67357: {
  skip_1904X = arg0K0;
  merged_arg0K0 = (*((unsigned char *) ((Scode_pointerS) + 1)));
#ifdef USE_DIRECT_THREADING
  move_args_above_contB_return_address = &&move_args_above_contB_return_6;
#else
  move_args_above_contB_return_tag = 6;
#endif
  goto move_args_above_contB;
 move_args_above_contB_return_6:
  template_1905X = *((long *) (((char *) (-3 + (SvalS)))));
  arg0K0 = (*((long *) (((char *) (-3 + template_1905X)))));
  arg0K1 = skip_1904X;
  arg0K2 = (1 + skip_1904X);
  arg0K3 = template_1905X;
  goto L32468;}
 L32751: {
  skip_1906X = arg0K0;
  stack_arg_count_1907X = *((unsigned char *) ((Scode_pointerS) + 3));
  code_pointer_1908X = (Scode_pointerS) + ((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2))));
  ScontS = ((SstackS) + (PS_SHIFT_LEFT_INLINE(stack_arg_count_1907X, 3)));
  *((long *) (ScontS)) = (long) ((((long) code_pointer_1908X)));
  template_1909X = *((long *) (((char *) (-3 + (SvalS)))));
  arg0K0 = (*((long *) (((char *) (-3 + template_1909X)))));
  arg0K1 = skip_1906X;
  arg0K2 = (1 + skip_1906X);
  arg0K3 = template_1909X;
  goto L32468;}
 L32703: {
  skip_1910X = arg0K0;
  stack_arg_count_1911X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 3))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 4)));
  return_pointer_offset_1912X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + 1))), 8)) + (*((unsigned char *) ((Scode_pointerS) + 2)));
  if ((0 == return_pointer_offset_1912X)) {
    merged_arg0K0 = stack_arg_count_1911X;
#ifdef USE_DIRECT_THREADING
    move_args_above_contB_return_address = &&move_args_above_contB_return_7;
#else
    move_args_above_contB_return_tag = 7;
#endif
    goto move_args_above_contB;
   move_args_above_contB_return_7:
    goto L32708;}
  else {
    code_pointer_1913X = (Scode_pointerS) + return_pointer_offset_1912X;
    ScontS = ((SstackS) + (PS_SHIFT_LEFT_INLINE(stack_arg_count_1911X, 3)));
    *((long *) (ScontS)) = (long) ((((long) code_pointer_1913X)));
    goto L32708;}}
 L67370: {
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L65449: {
  stack_arg_count_1914X = arg0K0;
  list_args_1915X = arg0K1;
  list_arg_count_1916X = arg0K2;
  if ((0 == list_arg_count_1916X)) {
    obj_1917X = SvalS;
    if ((3 == (3 & obj_1917X))) {
      if ((3 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_1917X))))), 2))))) {
        arg0K0 = stack_arg_count_1914X;
        arg0K1 = 25;
        arg0K2 = 0;
        arg0K3 = -1;
        goto L66500;}
      else {
        arg0K0 = 3;
        arg0K1 = stack_arg_count_1914X;
        arg0K2 = 25;
        arg0K3 = 0;
        goto L33486;}}
    else {
      arg0K0 = 3;
      arg0K1 = stack_arg_count_1914X;
      arg0K2 = 25;
      arg0K3 = 0;
      goto L33486;}}
  else {
    obj_1918X = SvalS;
    if ((3 == (3 & obj_1918X))) {
      if ((3 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_1918X))))), 2))))) {
        arg0K0 = stack_arg_count_1914X;
        arg0K1 = list_args_1915X;
        arg0K2 = list_arg_count_1916X;
        arg0K3 = -1;
        goto L66500;}
      else {
        arg0K0 = 3;
        arg0K1 = stack_arg_count_1914X;
        arg0K2 = list_args_1915X;
        arg0K3 = list_arg_count_1916X;
        goto L33486;}}
    else {
      arg0K0 = 3;
      arg0K1 = stack_arg_count_1914X;
      arg0K2 = list_args_1915X;
      arg0K3 = list_arg_count_1916X;
      goto L33486;}}}
 L23642: {
  list_args_1919X = arg0K0;
  stack_nargs_1920X = arg0K1;
  merged_arg0K0 = list_args_1919X;
#ifdef USE_DIRECT_THREADING
  okay_argument_list_return_address = &&okay_argument_list_return_2;
#else
  okay_argument_list_return_tag = 2;
#endif
  goto okay_argument_list;
 okay_argument_list_return_2:
  okayP_1921X = okay_argument_list0_return_value;
  list_arg_count_1922X = okay_argument_list1_return_value;
  if (okayP_1921X) {
    arg0K0 = stack_nargs_1920X;
    arg0K1 = list_args_1919X;
    arg0K2 = list_arg_count_1922X;
    goto L65449;}
  else {
    merged_arg0K0 = list_args_1919X;
    merged_arg0K1 = stack_nargs_1920X;
#ifdef USE_DIRECT_THREADING
    pop_args_GlistSAgc_return_address = &&pop_args_GlistSAgc_return_3;
#else
    pop_args_GlistSAgc_return_tag = 3;
#endif
    goto pop_args_GlistSAgc;
   pop_args_GlistSAgc_return_3:
    args_1923X = pop_args_GlistSAgc0_return_value;push_exception_setupB(5, 0);
    x_1924X = SvalS;
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (x_1924X);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (args_1923X);
    arg0K0 = 2;
    goto L33796;}}
 L23687: {
  list_1925X = arg0K0;
  follower_1926X = arg0K1;
  if ((25 == list_1925X)) {
    list_args_1927X = *((long *) (((char *) (-3 + (*((long *) ((((char *) (-3 + follower_1926X))) + 8)))))));
    addr_1928X = (((char *) (-3 + follower_1926X))) + 8;S48_WRITE_BARRIER(follower_1926X, addr_1928X, list_args_1927X);
    *((long *) addr_1928X) = (long) (list_args_1927X);
    arg0K0 = rest_list_1301X;
    arg0K1 = (-1 + stack_nargs_1300X);
    goto L23642;}
  else {
    arg0K0 = (*((long *) ((((char *) (-3 + list_1925X))) + 8)));
    arg0K1 = (*((long *) ((((char *) (-3 + follower_1926X))) + 8)));
    goto L23687;}}
 L33557: {
  obj_1929X = SvalS;
  if ((3 == (3 & obj_1929X))) {
    if ((3 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_1929X))))), 2))))) {
      arg0K0 = 0;
      arg0K1 = 25;
      arg0K2 = 0;
      arg0K3 = -1;
      goto L66500;}
    else {
      arg0K0 = 3;
      arg0K1 = 0;
      arg0K2 = 25;
      arg0K3 = 0;
      goto L33486;}}
  else {
    arg0K0 = 3;
    arg0K1 = 0;
    arg0K2 = 25;
    arg0K3 = 0;
    goto L33486;}}
 L33566: {
  SstackS = (Sbottom_of_stackS);
  Sheap_continuationS = cont_1303X;
  ScontS = (Sbottom_of_stackS);
  goto L33557;}
 L66038: {
  code_pointer_1930X = ((char *) (*((long *) (ScontS))));
  protocol_1931X = *((unsigned char *) (code_pointer_1930X + 1));
  if ((1 == protocol_1931X)) {
    goto L66055;}
  else {
    if ((66 == protocol_1931X)) {
      goto L66055;}
    else {
      if ((129 == protocol_1931X)) {
        arg0K0 = 2;
        goto L65840;}
      else {
        if ((194 == protocol_1931X)) {
          arg0K0 = 2;
          goto L65840;}
        else {
          if ((71 == protocol_1931X)) {
            cont_1932X = Sheap_continuationS;
            if ((3 == (3 & cont_1932X))) {
              if ((10 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + cont_1932X))))), 2))))) {
                merged_arg0K0 = cont_1932X;
                merged_arg0K1 = 0;
#ifdef USE_DIRECT_THREADING
                copy_continuation_from_heapB_return_address = &&copy_continuation_from_heapB_return_1;
#else
                copy_continuation_from_heapB_return_tag = 1;
#endif
                goto copy_continuation_from_heapB;
               copy_continuation_from_heapB_return_1:
                goto L66038;}
              else {
                arg0K0 = cont_1932X;
                goto L34158;}}
            else {
              arg0K0 = cont_1932X;
              goto L34158;}}
          else {
            if ((70 == protocol_1931X)) {
              offset_1933X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (code_pointer_1930X + 2))), 8)) + (*((unsigned char *) (code_pointer_1930X + 3)));
              proc_1934X = *((long *) ((ScontS) + 8));
              if ((0 == offset_1933X)) {
                cont_1935X = ScontS;
                pointer_1936X = (((char *) (*((long *) cont_1935X)))) + -2;
                size_1937X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) pointer_1936X)), 8)) + (*((unsigned char *) (pointer_1936X + 1)));
                if ((65535 == size_1937X)) {
                  arg0K0 = (PS_SHIFT_RIGHT_INLINE((*((long *) (cont_1935X + 8))), 2));
                  goto L66199;}
                else {
                  arg0K0 = size_1937X;
                  goto L66199;}}
              else {
                ScontS = ((ScontS) + 8);
                *((long *) (ScontS)) = (long) ((((long) (code_pointer_1930X + offset_1933X))));
                SstackS = (ScontS);
                goto L66104;}}
            else {
              if ((65 == protocol_1931X)) {
                wants_stack_args_1938X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (code_pointer_1930X + 2))), 8)) + (*((unsigned char *) (code_pointer_1930X + 3)));
                if ((0 == wants_stack_args_1938X)) {
#ifdef USE_DIRECT_THREADING
                  pop_continuationB_return_address = &&pop_continuationB_return_0;
#else
                  pop_continuationB_return_tag = 0;
#endif
                  goto pop_continuationB;
                 pop_continuationB_return_0:s48_make_availableAgc(24);
                  a_1939X = SvalS;
                  addr_1940X = s48_allocate_small(24);
                  *((long *) addr_1940X) = (long) (4098);
                  x_1941X = 3 + (((long) (addr_1940X + 8)));
                  *((long *) (((char *) (-3 + x_1941X)))) = (long) (a_1939X);
                  *((long *) ((((char *) (-3 + x_1941X))) + 8)) = (long) (25);
                  SstackS = ((SstackS) + -8);
                  *((long *) (SstackS)) = (long) (x_1941X);
                  Scode_pointerS = ((Scode_pointerS) + 4);
                  arg3K0 = (Scode_pointerS);
                  goto L36237;}
                else {
                  if ((1 == wants_stack_args_1938X)) {
#ifdef USE_DIRECT_THREADING
                    pop_continuationB_return_address = &&pop_continuationB_return_1;
#else
                    pop_continuationB_return_tag = 1;
#endif
                    goto pop_continuationB;
                   pop_continuationB_return_1:
                    x_1942X = SvalS;
                    SstackS = ((SstackS) + -8);
                    *((long *) (SstackS)) = (long) (x_1942X);
                    SstackS = ((SstackS) + -8);
                    *((long *) (SstackS)) = (long) (25);
                    Scode_pointerS = ((Scode_pointerS) + 4);
                    arg3K0 = (Scode_pointerS);
                    goto L36237;}
                  else {
                    x_1943X = SvalS;
                    SstackS = ((SstackS) + -8);
                    *((long *) (SstackS)) = (long) (x_1943X);
                    merged_arg0K0 = 25;
                    merged_arg0K1 = 1;
#ifdef USE_DIRECT_THREADING
                    pop_args_GlistSAgc_return_address = &&pop_args_GlistSAgc_return_4;
#else
                    pop_args_GlistSAgc_return_tag = 4;
#endif
                    goto pop_args_GlistSAgc;
                   pop_args_GlistSAgc_return_4:
                    args_1944X = pop_args_GlistSAgc0_return_value;push_exception_setupB(4, 0);
                    SstackS = ((SstackS) + -8);
                    *((long *) (SstackS)) = (long) (1);
                    SstackS = ((SstackS) + -8);
                    *((long *) (SstackS)) = (long) (args_1944X);
                    arg0K0 = 2;
                    goto L33796;}}}
              else {
                x_1945X = SvalS;
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) (x_1945X);
                merged_arg0K0 = 25;
                merged_arg0K1 = 1;
#ifdef USE_DIRECT_THREADING
                pop_args_GlistSAgc_return_address = &&pop_args_GlistSAgc_return_5;
#else
                pop_args_GlistSAgc_return_tag = 5;
#endif
                goto pop_args_GlistSAgc;
               pop_args_GlistSAgc_return_5:
                args_1946X = pop_args_GlistSAgc0_return_value;push_exception_setupB(4, 0);
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) (1);
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) (args_1946X);
                arg0K0 = 2;
                goto L33796;}}}}}}}}
 L33224: {
  stack_nargs_1947X = arg0K0;
  list_args_1948X = arg0K1;
  list_arg_count_1949X = arg0K2;
  code_pointer_1950X = ((char *) (*((long *) (ScontS))));
  protocol_1951X = *((unsigned char *) (code_pointer_1950X + 1));
  if ((1 == protocol_1951X)) {
    if ((1 == (stack_nargs_1947X + list_arg_count_1949X))) {
      if ((1 == stack_nargs_1947X)) {
        v_1952X = *((long *) (SstackS));
        SstackS = ((SstackS) + 8);
        arg0K0 = v_1952X;
        goto L33313;}
      else {
        arg0K0 = (*((long *) (((char *) (-3 + list_args_1948X)))));
        goto L33313;}}
    else {
      arg0K0 = stack_nargs_1947X;
      arg0K1 = list_args_1948X;
      goto L34241;}}
  else {
    if ((66 == protocol_1951X)) {
#ifdef USE_DIRECT_THREADING
      pop_continuationB_return_address = &&pop_continuationB_return_2;
#else
      pop_continuationB_return_tag = 2;
#endif
      goto pop_continuationB;
     pop_continuationB_return_2:
      arg0K0 = 1;
      goto L36671;}
    else {
      if ((127 < protocol_1951X)) {
        if ((129 == protocol_1951X)) {
          if ((1 == (stack_nargs_1947X + list_arg_count_1949X))) {
            if ((1 == stack_nargs_1947X)) {
              v_1953X = *((long *) (SstackS));
              SstackS = ((SstackS) + 8);
              arg0K0 = v_1953X;
              goto L66384;}
            else {
              arg0K0 = (*((long *) (((char *) (-3 + list_args_1948X)))));
              goto L66384;}}
          else {
            merged_arg0K0 = list_args_1948X;
            merged_arg0K1 = stack_nargs_1947X;
#ifdef USE_DIRECT_THREADING
            pop_args_GlistSAgc_return_address = &&pop_args_GlistSAgc_return_6;
#else
            pop_args_GlistSAgc_return_tag = 6;
#endif
            goto pop_args_GlistSAgc;
           pop_args_GlistSAgc_return_6:
            args_1954X = pop_args_GlistSAgc0_return_value;push_exception_setupB(4, 0);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (1);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (args_1954X);
            arg0K0 = 2;
            goto L33796;}}
        else {
          if ((194 == protocol_1951X)) {
            arg0K0 = 2;
            goto L65840;}
          else {
            ps_error("unknown native return protocol", 1, protocol_1951X);
            merged_arg0K0 = list_args_1948X;
            merged_arg0K1 = stack_nargs_1947X;
#ifdef USE_DIRECT_THREADING
            pop_args_GlistSAgc_return_address = &&pop_args_GlistSAgc_return_7;
#else
            pop_args_GlistSAgc_return_tag = 7;
#endif
            goto pop_args_GlistSAgc;
           pop_args_GlistSAgc_return_7:
            args_1955X = pop_args_GlistSAgc0_return_value;push_exception_setupB(4, 0);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (1);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (args_1955X);
            arg0K0 = 2;
            goto L33796;}}}
      else {
        if ((71 == protocol_1951X)) {
          cont_1956X = Sheap_continuationS;
          if ((3 == (3 & cont_1956X))) {
            if ((10 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + cont_1956X))))), 2))))) {
              merged_arg0K0 = cont_1956X;
              merged_arg0K1 = stack_nargs_1947X;
#ifdef USE_DIRECT_THREADING
              copy_continuation_from_heapB_return_address = &&copy_continuation_from_heapB_return_2;
#else
              copy_continuation_from_heapB_return_tag = 2;
#endif
              goto copy_continuation_from_heapB;
             copy_continuation_from_heapB_return_2:
              arg0K0 = stack_nargs_1947X;
              arg0K1 = list_args_1948X;
              arg0K2 = list_arg_count_1949X;
              goto L33224;}
            else {
              goto L33259;}}
          else {
            goto L33259;}}
        else {
          if ((70 == protocol_1951X)) {
            SvalS = (*((long *) ((ScontS) + 8)));
            offset_1957X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (code_pointer_1950X + 2))), 8)) + (*((unsigned char *) (code_pointer_1950X + 3)));
            if ((0 == offset_1957X)) {
              cont_1958X = ScontS;
              pointer_1959X = (((char *) (*((long *) cont_1958X)))) + -2;
              size_1960X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) pointer_1959X)), 8)) + (*((unsigned char *) (pointer_1959X + 1)));
              if ((65535 == size_1960X)) {
                arg0K0 = (PS_SHIFT_RIGHT_INLINE((*((long *) (cont_1958X + 8))), 2));
                goto L33376;}
              else {
                arg0K0 = size_1960X;
                goto L33376;}}
            else {
              ScontS = ((ScontS) + 8);
              *((long *) (ScontS)) = (long) ((((long) (code_pointer_1950X + offset_1957X))));
              merged_arg0K0 = stack_nargs_1947X;
#ifdef USE_DIRECT_THREADING
              move_args_above_contB_return_address = &&move_args_above_contB_return_8;
#else
              move_args_above_contB_return_tag = 8;
#endif
              goto move_args_above_contB;
             move_args_above_contB_return_8:
              arg0K0 = stack_nargs_1947X;
              arg0K1 = list_args_1948X;
              arg0K2 = list_arg_count_1949X;
              goto L65449;}}
          else {
            if ((63 < protocol_1951X)) {
              if ((65 == protocol_1951X)) {
                count_1961X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (code_pointer_1950X + 2))), 8)) + (*((unsigned char *) (code_pointer_1950X + 3)));
                if (((stack_nargs_1947X + list_arg_count_1949X) < count_1961X)) {
                  merged_arg0K0 = list_args_1948X;
                  merged_arg0K1 = stack_nargs_1947X;
#ifdef USE_DIRECT_THREADING
                  pop_args_GlistSAgc_return_address = &&pop_args_GlistSAgc_return_8;
#else
                  pop_args_GlistSAgc_return_tag = 8;
#endif
                  goto pop_args_GlistSAgc;
                 pop_args_GlistSAgc_return_8:
                  args_1962X = pop_args_GlistSAgc0_return_value;push_exception_setupB(4, 0);
                  SstackS = ((SstackS) + -8);
                  *((long *) (SstackS)) = (long) (1);
                  SstackS = ((SstackS) + -8);
                  *((long *) (SstackS)) = (long) (args_1962X);
                  arg0K0 = 2;
                  goto L33796;}
                else {
                  arg_top_1963X = SstackS;
#ifdef USE_DIRECT_THREADING
                  pop_continuationB_return_address = &&pop_continuationB_return_3;
#else
                  pop_continuationB_return_tag = 3;
#endif
                  goto pop_continuationB;
                 pop_continuationB_return_3:
                  arg3K0 = ((SstackS) + -8);
                  arg3K1 = (arg_top_1963X + (-8 + (PS_SHIFT_LEFT_INLINE(stack_nargs_1947X, 3))));
                  goto L37728;}}
              else {
                if ((64 == protocol_1951X)) {
                  arg0K0 = ((PS_SHIFT_LEFT_INLINE((*((unsigned char *) (code_pointer_1950X + 2))), 8)) + (*((unsigned char *) (code_pointer_1950X + 3))));
                  arg0K1 = 3;
                  arg0K2 = stack_nargs_1947X;
                  arg0K3 = list_args_1948X;
                  arg0K4 = list_arg_count_1949X;
                  goto L37580;}
                else {
                  ps_error("unknown protocol", 1, protocol_1951X);
                  arg0K0 = stack_nargs_1947X;
                  arg0K1 = list_args_1948X;
                  goto L34241;}}}
            else {
              arg0K0 = protocol_1951X;
              arg0K1 = 1;
              arg0K2 = stack_nargs_1947X;
              arg0K3 = list_args_1948X;
              arg0K4 = list_arg_count_1949X;
              goto L37580;}}}}}}}
 L37880: {
  if ((nargs_1310X == (*((unsigned char *) ((((char *) (-3 + code_1309X))) + 1))))) {
    arg0K0 = code_1309X;
    arg0K1 = 2;
    arg0K2 = 3;
    arg0K3 = template_1308X;
    goto L32468;}
  else {
    v_1964X = *((unsigned char *) ((((char *) (-3 + code_1309X))) + 1));
    if ((67 == v_1964X)) {
      if ((nargs_1310X == (*((unsigned char *) ((((char *) (-3 + code_1309X))) + (-3 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + code_1309X))))), 8)))))))) {
        index_1965X = -2 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + code_1309X))))), 8));
        arg0K0 = code_1309X;
        arg0K1 = 2;
        arg0K2 = template_1308X;
        arg0K3 = ((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((((char *) (-3 + code_1309X))) + index_1965X))), 8)) + (*((unsigned char *) ((((char *) (-3 + code_1309X))) + (1 + index_1965X)))));
        goto L36681;}
      else {
        goto L37902;}}
    else {
      goto L37902;}}}
 L36556: {
  arg0K0 = (2 + (PS_SHIFT_LEFT_INLINE(max_1314X, 1)));
  goto L36558;}
 L36558: {
  offset_1966X = arg0K0;
  Scode_pointerS = ((Scode_pointerS) + offset_1966X);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L37145: {
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L36454: {
  delta_1967X = arg0K0;
  Scode_pointerS = ((Scode_pointerS) + delta_1967X);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L37036: {
  delta_1968X = arg0K0;
  Scode_pointerS = ((Scode_pointerS) + delta_1968X);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L67418: {
  val_1969X = arg0K0;
  SvalS = val_1969X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L67430: {
  val_1970X = arg0K0;
  SvalS = val_1970X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L21059: {
  if ((3 == (3 & x_1329X))) {
    if ((8 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + x_1329X))))), 2))))) {
      arg0K0 = 5;
      goto L67430;}
    else {
      goto L21065;}}
  else {
    goto L21065;}}
 L56372: {
  SvalS = 5;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L56373: {
  if ((3 == (3 & n_1330X))) {
    if ((11 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + n_1330X))))), 2))))) {
      goto L56386;}
    else {
      goto L56381;}}
  else {
    goto L56381;}}
 L56529: {
  SvalS = 5;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L56522: {
  if ((3 == (3 & n_1331X))) {
    if ((8 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + n_1331X))))), 2))))) {
      goto L56529;}
    else {
      goto L56530;}}
  else {
    goto L56530;}}
 L56732: {
  n_1971X = arg0K0;
  if ((0 == (3 & n_1971X))) {
    goto L56765;}
  else {
    if ((3 == (3 & n_1971X))) {
      if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + n_1971X))))), 2))))) {
        goto L56765;}
      else {
        goto L56748;}}
    else {
      goto L56748;}}}
 L47869: {
  SvalS = 5;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L47870: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (n_1332X);
  arg0K0 = 1;
  goto L33796;}
 L47995: {
  v_1972X = (char *) s48_long_to_bignum(x_1337X);
  v_1973X = enter_bignum(v_1972X);
  arg0K0 = v_1973X;
  goto L47941;}
 L47941: {
  val_1974X = arg0K0;
  SvalS = val_1974X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L47947: {
  if ((0 == (3 & y_1336X))) {
    goto L47953;}
  else {
    if ((3 == (3 & y_1336X))) {
      if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1336X))))), 2))))) {
        goto L47953;}
      else {
        goto L47956;}}
    else {
      goto L47956;}}}
 L47956: {
  if ((3 == (3 & arg2_1335X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1335X))))), 2))))) {
      if ((3 == (3 & y_1336X))) {
        if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1336X))))), 2))))) {
          Stemp0S = arg2_1335X;
          Stemp1S = y_1336X;s48_make_availableAgc(16);
          value_1975X = Stemp0S;
          Stemp0S = 1;
          x_1976X = *((double *) (((char *) (-3 + value_1975X))));
          value_1977X = Stemp1S;
          Stemp1S = 1;
          y_1978X = *((double *) (((char *) (-3 + value_1977X))));
          addr_1979X = s48_allocate_small(16);
          *((long *) addr_1979X) = (long) (2122);
          Kdouble_1980X = 3 + (((long) (addr_1979X + 8)));
          *((double *) (((char *) (-3 + Kdouble_1980X)))) = (double) ((x_1976X + y_1978X));
          SvalS = Kdouble_1980X;
          Scode_pointerS = ((Scode_pointerS) + 1);
          arg3K0 = (Scode_pointerS);
          goto L36237;}
        else {
          goto L47970;}}
      else {
        goto L47970;}}
    else {
      goto L47970;}}
  else {
    goto L47970;}}
 L12468: {
  a_1981X = arg0K0;
  if ((b_1341X < 0)) {
    arg0K0 = (0 - b_1341X);
    goto L12472;}
  else {
    arg0K0 = b_1341X;
    goto L12472;}}
 L58516: {
  if ((0 == (3 & y_1339X))) {
    goto L58522;}
  else {
    if ((3 == (3 & y_1339X))) {
      if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1339X))))), 2))))) {
        goto L58522;}
      else {
        goto L58525;}}
    else {
      goto L58525;}}}
 L58525: {
  if ((3 == (3 & arg2_1338X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1338X))))), 2))))) {
      if ((3 == (3 & y_1339X))) {
        if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1339X))))), 2))))) {
          Stemp0S = arg2_1338X;
          Stemp1S = y_1339X;s48_make_availableAgc(16);
          value_1982X = Stemp0S;
          Stemp0S = 1;
          x_1983X = *((double *) (((char *) (-3 + value_1982X))));
          value_1984X = Stemp1S;
          Stemp1S = 1;
          y_1985X = *((double *) (((char *) (-3 + value_1984X))));
          addr_1986X = s48_allocate_small(16);
          *((long *) addr_1986X) = (long) (2122);
          Kdouble_1987X = 3 + (((long) (addr_1986X + 8)));
          *((double *) (((char *) (-3 + Kdouble_1987X)))) = (double) ((x_1983X * y_1985X));
          SvalS = Kdouble_1987X;
          Scode_pointerS = ((Scode_pointerS) + 1);
          arg3K0 = (Scode_pointerS);
          goto L36237;}
        else {
          goto L58539;}}
      else {
        goto L58539;}}
    else {
      goto L58539;}}
  else {
    goto L58539;}}
 L48284: {
  v_1988X = (char *) s48_long_to_bignum(x_1344X);
  v_1989X = enter_bignum(v_1988X);
  arg0K0 = v_1989X;
  goto L48230;}
 L48230: {
  val_1990X = arg0K0;
  SvalS = val_1990X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L48236: {
  if ((0 == (3 & y_1343X))) {
    goto L48242;}
  else {
    if ((3 == (3 & y_1343X))) {
      if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1343X))))), 2))))) {
        goto L48242;}
      else {
        goto L48245;}}
    else {
      goto L48245;}}}
 L48245: {
  if ((3 == (3 & arg2_1342X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1342X))))), 2))))) {
      if ((3 == (3 & y_1343X))) {
        if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1343X))))), 2))))) {
          Stemp0S = arg2_1342X;
          Stemp1S = y_1343X;s48_make_availableAgc(16);
          value_1991X = Stemp0S;
          Stemp0S = 1;
          x_1992X = *((double *) (((char *) (-3 + value_1991X))));
          value_1993X = Stemp1S;
          Stemp1S = 1;
          y_1994X = *((double *) (((char *) (-3 + value_1993X))));
          addr_1995X = s48_allocate_small(16);
          *((long *) addr_1995X) = (long) (2122);
          Kdouble_1996X = 3 + (((long) (addr_1995X + 8)));
          *((double *) (((char *) (-3 + Kdouble_1996X)))) = (double) ((x_1992X - y_1994X));
          SvalS = Kdouble_1996X;
          Scode_pointerS = ((Scode_pointerS) + 1);
          arg3K0 = (Scode_pointerS);
          goto L36237;}
        else {
          goto L48259;}}
      else {
        goto L48259;}}
    else {
      goto L48259;}}
  else {
    goto L48259;}}
 L12726: {
  a_1997X = arg0K0;
  if ((b_1348X < 0)) {
    arg0K0 = (0 - b_1348X);
    goto L12730;}
  else {
    arg0K0 = b_1348X;
    goto L12730;}}
 L58769: {
  if ((0 == (3 & y_1346X))) {
    goto L58775;}
  else {
    if ((3 == (3 & y_1346X))) {
      if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1346X))))), 2))))) {
        goto L58775;}
      else {
        goto L58806;}}
    else {
      goto L58806;}}}
 L58806: {
  if ((3 == (3 & arg2_1345X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1345X))))), 2))))) {
      if ((3 == (3 & y_1346X))) {
        if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1346X))))), 2))))) {
          Stemp0S = arg2_1345X;
          Stemp1S = y_1346X;s48_make_availableAgc(16);
          value_1998X = Stemp0S;
          Stemp0S = 1;
          x_1999X = *((double *) (((char *) (-3 + value_1998X))));
          value_2000X = Stemp1S;
          Stemp1S = 1;
          value_2001X = x_1999X / (*((double *) (((char *) (-3 + value_2000X)))));
          addr_2002X = s48_allocate_small(16);
          *((long *) addr_2002X) = (long) (2122);
          Kdouble_2003X = 3 + (((long) (addr_2002X + 8)));
          *((double *) (((char *) (-3 + Kdouble_2003X)))) = (double) (value_2001X);
          SvalS = Kdouble_2003X;
          Scode_pointerS = ((Scode_pointerS) + 1);
          arg3K0 = (Scode_pointerS);
          goto L36237;}
        else {
          goto L58820;}}
      else {
        goto L58820;}}
    else {
      goto L58820;}}
  else {
    goto L58820;}}
 L48515: {
  val_2004X = arg0K0;
  SvalS = val_2004X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L48521: {
  if ((0 == (3 & y_1350X))) {
    goto L48527;}
  else {
    if ((3 == (3 & y_1350X))) {
      if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1350X))))), 2))))) {
        goto L48527;}
      else {
        goto L48532;}}
    else {
      goto L48532;}}}
 L48532: {
  if ((3 == (3 & arg2_1349X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1349X))))), 2))))) {
      if ((3 == (3 & y_1350X))) {
        if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1350X))))), 2))))) {
          b_2005X = (*((double *) (((char *) (-3 + arg2_1349X))))) == (*((double *) (((char *) (-3 + y_1350X)))));
          if (b_2005X) {
            arg0K0 = 5;
            goto L48547;}
          else {
            arg0K0 = 1;
            goto L48547;}}
        else {
          goto L48548;}}
      else {
        goto L48548;}}
    else {
      goto L48548;}}
  else {
    goto L48548;}}
 L48775: {
  val_2006X = arg0K0;
  SvalS = val_2006X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L48781: {
  if ((0 == (3 & y_1352X))) {
    goto L48787;}
  else {
    if ((3 == (3 & y_1352X))) {
      if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1352X))))), 2))))) {
        goto L48787;}
      else {
        goto L48792;}}
    else {
      goto L48792;}}}
 L48792: {
  if ((3 == (3 & arg2_1351X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1351X))))), 2))))) {
      if ((3 == (3 & y_1352X))) {
        if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1352X))))), 2))))) {
          b_2007X = (*((double *) (((char *) (-3 + arg2_1351X))))) < (*((double *) (((char *) (-3 + y_1352X)))));
          if (b_2007X) {
            arg0K0 = 5;
            goto L48807;}
          else {
            arg0K0 = 1;
            goto L48807;}}
        else {
          goto L48808;}}
      else {
        goto L48808;}}
    else {
      goto L48808;}}
  else {
    goto L48808;}}
 L49098: {
  val_2008X = arg0K0;
  SvalS = val_2008X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L49104: {
  if ((0 == (3 & y_1354X))) {
    goto L49110;}
  else {
    if ((3 == (3 & y_1354X))) {
      if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1354X))))), 2))))) {
        goto L49110;}
      else {
        goto L49115;}}
    else {
      goto L49115;}}}
 L49115: {
  if ((3 == (3 & arg2_1353X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1353X))))), 2))))) {
      if ((3 == (3 & y_1354X))) {
        if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1354X))))), 2))))) {
          b_2009X = (*((double *) (((char *) (-3 + y_1354X))))) < (*((double *) (((char *) (-3 + arg2_1353X)))));
          if (b_2009X) {
            arg0K0 = 5;
            goto L49130;}
          else {
            arg0K0 = 1;
            goto L49130;}}
        else {
          goto L49131;}}
      else {
        goto L49131;}}
    else {
      goto L49131;}}
  else {
    goto L49131;}}
 L49421: {
  val_2010X = arg0K0;
  SvalS = val_2010X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L49427: {
  if ((0 == (3 & y_1356X))) {
    goto L49433;}
  else {
    if ((3 == (3 & y_1356X))) {
      if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1356X))))), 2))))) {
        goto L49433;}
      else {
        goto L49438;}}
    else {
      goto L49438;}}}
 L49438: {
  if ((3 == (3 & arg2_1355X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1355X))))), 2))))) {
      if ((3 == (3 & y_1356X))) {
        if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1356X))))), 2))))) {
          if (((*((double *) (((char *) (-3 + y_1356X))))) < (*((double *) (((char *) (-3 + arg2_1355X))))))) {
            arg0K0 = 1;
            goto L49453;}
          else {
            arg0K0 = 5;
            goto L49453;}}
        else {
          goto L49454;}}
      else {
        goto L49454;}}
    else {
      goto L49454;}}
  else {
    goto L49454;}}
 L49715: {
  val_2011X = arg0K0;
  SvalS = val_2011X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L49721: {
  if ((0 == (3 & y_1358X))) {
    goto L49727;}
  else {
    if ((3 == (3 & y_1358X))) {
      if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1358X))))), 2))))) {
        goto L49727;}
      else {
        goto L49732;}}
    else {
      goto L49732;}}}
 L49732: {
  if ((3 == (3 & arg2_1357X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1357X))))), 2))))) {
      if ((3 == (3 & y_1358X))) {
        if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1358X))))), 2))))) {
          if (((*((double *) (((char *) (-3 + arg2_1357X))))) < (*((double *) (((char *) (-3 + y_1358X))))))) {
            arg0K0 = 1;
            goto L49747;}
          else {
            arg0K0 = 5;
            goto L49747;}}
        else {
          goto L49748;}}
      else {
        goto L49748;}}
    else {
      goto L49748;}}
  else {
    goto L49748;}}
 L13141: {
  a_2012X = arg0K0;
  if ((b_1363X < 0)) {
    arg0K0 = (0 - b_1363X);
    goto L13145;}
  else {
    arg0K0 = b_1363X;
    goto L13145;}}
 L50021: {
  if ((0 == (3 & y_1360X))) {
    goto L50027;}
  else {
    if ((3 == (3 & y_1360X))) {
      if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1360X))))), 2))))) {
        goto L50027;}
      else {
        goto L50030;}}
    else {
      goto L50030;}}}
 L50030: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1359X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (y_1360X);
  arg0K0 = 2;
  goto L33796;}
 L50235: {
  a_2013X = arg0K0;
  n_2014X = PS_SHIFT_RIGHT_INLINE(y_1365X, 2);
  if ((n_2014X < 0)) {
    arg0K0 = (0 - n_2014X);
    goto L50237;}
  else {
    arg0K0 = n_2014X;
    goto L50237;}}
 L50197: {
  if ((0 == (3 & y_1365X))) {
    goto L50203;}
  else {
    if ((3 == (3 & y_1365X))) {
      if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1365X))))), 2))))) {
        goto L50203;}
      else {
        goto L50206;}}
    else {
      goto L50206;}}}
 L50206: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1364X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (y_1365X);
  arg0K0 = 2;
  goto L33796;}
 L50384: {
  SvalS = n_1368X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L50385: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (n_1368X);
  arg0K0 = 1;
  goto L33796;}
 L50439: {
  SvalS = n_1369X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L50440: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (n_1369X);
  arg0K0 = 1;
  goto L33796;}
 L50494: {
  SvalS = 4;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L50497: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (n_1370X);
  arg0K0 = 1;
  goto L33796;}
 L50554: {
  SvalS = n_1371X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L50555: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (n_1371X);
  arg0K0 = 1;
  goto L33796;}
 L50609: {
  SvalS = 0;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L50612: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (n_1372X);
  arg0K0 = 1;
  goto L33796;}
 L60096: {
  x_2015X = SvalS;
  if ((0 == (3 & x_2015X))) {
    if ((0 < x_2015X)) {
      goto L60125;}
    else {
      goto L60119;}}
  else {
    v_2016X = s48_bignum_test((((char *) (-3 + x_2015X))));
    if ((-1 == v_2016X)) {
      goto L60119;}
    else {
      goto L60125;}}}
 L60099: {
push_exception_setupB(5, 1);
  x_2017X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2017X);
  arg0K0 = 1;
  goto L33796;}
 L63554: {
  x_2018X = SvalS;
  if ((0 == (3 & x_2018X))) {
    n_2019X = PS_SHIFT_RIGHT_INLINE(x_2018X, 2);
    if ((n_2019X < 0)) {
      arg0K0 = (0 - n_2019X);
      goto L59106;}
    else {
      arg0K0 = n_2019X;
      goto L59106;}}
  else {
    if ((0 == (3 & x_2018X))) {
      arg0K0 = 1;
      arg0K1 = 3;
      goto L26713;}
    else {
      arg0K0 = (-1 + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + x_2018X))))), 8))), 3)));
      arg0K1 = 0;
      goto L26713;}}}
 L63557: {
push_exception_setupB(5, 1);
  x_2020X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2020X);
  arg0K0 = 1;
  goto L33796;}
 L50755: {
  val_2021X = integer_bitwise_not(x_1390X);
  SvalS = val_2021X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L50758: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_1390X);
  arg0K0 = 1;
  goto L33796;}
 L50846: {
  x_2022X = arg0K0;
  arg0K0 = x_2022X;
  arg0K1 = 0;
  goto L50852;}
 L50829: {
  val_2023X = integer_bit_count(x_1391X);
  SvalS = val_2023X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L50832: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_1391X);
  arg0K0 = 1;
  goto L33796;}
 L50931: {
  if ((0 == (3 & y_1394X))) {
    goto L50937;}
  else {
    if ((3 == (3 & y_1394X))) {
      if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1394X))))), 2))))) {
        goto L50937;}
      else {
        goto L50940;}}
    else {
      goto L50940;}}}
 L50940: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1393X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (y_1394X);
  arg0K0 = 2;
  goto L33796;}
 L51094: {
  if ((0 == (3 & y_1396X))) {
    goto L51100;}
  else {
    if ((3 == (3 & y_1396X))) {
      if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1396X))))), 2))))) {
        goto L51100;}
      else {
        goto L51103;}}
    else {
      goto L51103;}}}
 L51103: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1395X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (y_1396X);
  arg0K0 = 2;
  goto L33796;}
 L51257: {
  if ((0 == (3 & y_1398X))) {
    goto L51263;}
  else {
    if ((3 == (3 & y_1398X))) {
      if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + y_1398X))))), 2))))) {
        goto L51263;}
      else {
        goto L51266;}}
    else {
      goto L51266;}}}
 L51266: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1397X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (y_1398X);
  arg0K0 = 2;
  goto L33796;}
 L47649: {
  val_2024X = arg0K0;
  SvalS = val_2024X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L47665: {
  val_2025X = arg0K0;
  SvalS = val_2025X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L47666: {
push_exception_setupB(7, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1399X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (y_1400X);
  arg0K0 = 2;
  goto L33796;}
 L59156: {
  if ((0 == (3 & y_1400X))) {
    if ((0 == (3 & arg2_1399X))) {
      value_2026X = PS_SHIFT_RIGHT_INLINE(arg2_1399X, 2);
      count_2027X = PS_SHIFT_RIGHT_INLINE(y_1400X, 2);
      if ((count_2027X < 0)) {
        PS_SHIFT_RIGHT(value_2026X, (0 - count_2027X), x_2028X)
        x_2029X = x_2028X;s48_make_availableAgc(24);
        if ((2305843009213693951 < x_2029X)) {
          goto L59276;}
        else {
          if ((x_2029X < -2305843009213693952)) {
            goto L59276;}
          else {
            arg0K0 = (PS_SHIFT_LEFT_INLINE(x_2029X, 2));
            goto L59271;}}}
      else {
        PS_SHIFT_LEFT(value_2026X, count_2027X, x_2030X)
        result_2031X = x_2030X;
        PS_SHIFT_RIGHT(result_2031X, count_2027X, x_2032X)
        if ((value_2026X == x_2032X)) {
          if ((value_2026X < 0)) {
            if ((result_2031X < 0)) {s48_make_availableAgc(24);
              if ((2305843009213693951 < result_2031X)) {
                goto L59298;}
              else {
                if ((result_2031X < -2305843009213693952)) {
                  goto L59298;}
                else {
                  arg0K0 = (PS_SHIFT_LEFT_INLINE(result_2031X, 2));
                  goto L59293;}}}
            else {
              arg0K0 = arg2_1399X;
              arg0K1 = y_1400X;
              goto L59169;}}
          else {
            if ((result_2031X < 0)) {
              arg0K0 = arg2_1399X;
              arg0K1 = y_1400X;
              goto L59169;}
            else {s48_make_availableAgc(24);
              if ((2305843009213693951 < result_2031X)) {
                goto L59320;}
              else {
                if ((result_2031X < -2305843009213693952)) {
                  goto L59320;}
                else {
                  arg0K0 = (PS_SHIFT_LEFT_INLINE(result_2031X, 2));
                  goto L59315;}}}}}
        else {
          arg0K0 = arg2_1399X;
          arg0K1 = y_1400X;
          goto L59169;}}}
    else {
      if ((3 == (3 & arg2_1399X))) {
        if ((19 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg2_1399X))))), 2))))) {
          y_2033X = PS_SHIFT_RIGHT_INLINE(y_1400X, 2);
          merged_arg0K0 = arg2_1399X;
          merged_arg0K1 = y_2033X;
#ifdef USE_DIRECT_THREADING
          shift_space_return_address = &&shift_space_return_0;
#else
          shift_space_return_tag = 0;
#endif
          goto shift_space;
         shift_space_return_0:
          needed_2034X = shift_space0_return_value;
          Stemp0S = arg2_1399X;s48_make_availableAgc((PS_SHIFT_LEFT_INLINE(needed_2034X, 3)));
          value_2035X = Stemp0S;
          Stemp0S = 1;
          if ((0 == (3 & value_2035X))) {
            v_2036X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_2035X, 2)));
            arg3K0 = v_2036X;
            goto L59351;}
          else {
            arg3K0 = (((char *) (-3 + value_2035X)));
            goto L59351;}}
        else {
          goto L59178;}}
      else {
        goto L59178;}}}
  else {push_exception_setupB(5, 1);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (arg2_1399X);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (y_1400X);
    arg0K0 = 2;
    goto L33796;}}
 L67689: {
  val_2037X = arg0K0;
  SvalS = val_2037X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L56173: {
  val_2038X = arg0K0;
  SvalS = val_2038X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L56144: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1404X);
  x_2039X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2039X);
  arg0K0 = 2;
  goto L33796;}
 L56081: {
  val_2040X = arg0K0;
  SvalS = val_2040X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L56052: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1406X);
  x_2041X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2041X);
  arg0K0 = 2;
  goto L33796;}
 L60405: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(x_1409X, 2)));
  arg0K0 = 1;
  goto L33796;}
 L60411: {
  SvalS = (9 + (PS_SHIFT_LEFT_INLINE(x_1409X, 8)));
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L55979: {
  val_2042X = arg0K0;
  SvalS = val_2042X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L67722: {
  val_2043X = arg0K0;
  SvalS = val_2043X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L67736: {
  value_2044X = arg0K0;
  SvalS = value_2044X;
  Scode_pointerS = ((Scode_pointerS) + 2);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L39018: {
push_exception_setupB(5, 2);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (stob_1416X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(type_1417X, 2)));
  arg0K0 = 2;
  goto L33796;}
 L39123: {
  SvalS = new_1422X;
  Scode_pointerS = ((Scode_pointerS) + 3);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L39107: {
  i_2045X = arg0K0;
  if ((i_2045X < 0)) {
    goto L39123;}
  else {
    value_2046X = *((long *) (SstackS));
    SstackS = ((SstackS) + 8);
    *((long *) ((((char *) (-3 + new_1422X))) + (PS_SHIFT_LEFT_INLINE(i_2045X, 3)))) = (long) (value_2046X);
    arg0K0 = (-1 + i_2045X);
    goto L39107;}}
 L39241: {
  i_2047X = arg0K0;
  if ((i_2047X < 0)) {
    arg0K0 = stack_nargs_1430X;
    arg0K1 = rest_list_1431X;
    goto L39383;}
  else {
    value_2048X = *((long *) (SstackS));
    SstackS = ((SstackS) + 8);
    *((long *) ((((char *) (-3 + new_1428X))) + (PS_SHIFT_LEFT_INLINE(i_2047X, 3)))) = (long) (value_2048X);
    arg0K0 = (-1 + i_2047X);
    goto L39241;}}
 L39409: {
push_exception_setupB(5, 3);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (stob_1432X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(type_1433X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(offset_1434X, 2)));
  arg0K0 = 3;
  goto L33796;}
 L39551: {
  addr_2049X = (((char *) (-3 + arg2_1435X))) + (PS_SHIFT_LEFT_INLINE(offset_1438X, 3));S48_WRITE_BARRIER(arg2_1435X, addr_2049X, value_1436X);
  *((long *) addr_2049X) = (long) (value_1436X);
  goto L39560;}
 L39560: {
  SvalS = 13;
  Scode_pointerS = ((Scode_pointerS) + 4);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L39519: {
push_exception_setupB(6, 4);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1435X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(type_1437X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(offset_1438X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (value_1436X);
  arg0K0 = 4;
  goto L33796;}
 L39576: {
push_exception_setupB(5, 4);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1435X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(type_1437X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(offset_1438X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (value_1436X);
  arg0K0 = 4;
  goto L33796;}
 L39777: {
push_exception_setupB(5, 2);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(type_1442X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(len_1443X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (init_1441X);
  arg0K0 = 3;
  goto L33796;}
 L39794: {
  x_2050X = arg0K0;
  value_2051X = Stemp0S;
  Stemp0S = 1;
  if ((1 == x_2050X)) {push_exception_setupB(9, 2);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(type_1442X, 2)));
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(len_1443X, 2)));
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (value_2051X);
    arg0K0 = 3;
    goto L33796;}
  else {
    arg0K0 = (-1 + len_1443X);
    goto L39820;}}
 L40067: {
push_exception_setupB(8, 3);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1446X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(type_1448X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (index_1447X);
  arg0K0 = 3;
  goto L33796;}
 L40057: {
  arg0K0 = (*((long *) ((((char *) (-3 + arg2_1446X))) + (PS_SHIFT_LEFT_INLINE((-4 & index_1447X), 1)))));
  goto L40066;}
 L40066: {
  value_2052X = arg0K0;
  SvalS = value_2052X;
  Scode_pointerS = ((Scode_pointerS) + 3);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L40022: {
push_exception_setupB(5, 3);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1446X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(type_1448X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (index_1447X);
  arg0K0 = 3;
  goto L33796;}
 L40360: {
push_exception_setupB(8, 3);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1454X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(type_1456X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1453X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (value_1455X);
  arg0K0 = 4;
  goto L33796;}
 L40350: {
  addr_2053X = (((char *) (-3 + arg3_1454X))) + (PS_SHIFT_LEFT_INLINE((-4 & arg2_1453X), 1));S48_WRITE_BARRIER(arg3_1454X, addr_2053X, value_1455X);
  *((long *) addr_2053X) = (long) (value_1455X);
  goto L40359;}
 L40359: {
  SvalS = 13;
  Scode_pointerS = ((Scode_pointerS) + 3);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L40313: {
push_exception_setupB(6, 3);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1454X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(type_1456X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1453X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (value_1455X);
  arg0K0 = 4;
  goto L33796;}
 L40297: {
push_exception_setupB(5, 3);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1454X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(type_1456X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1453X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (value_1455X);
  arg0K0 = 4;
  goto L33796;}
 L67779: {
  new_2054X = arg0K0;
  if ((1 == new_2054X)) {push_exception_setupB(9, 1);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (72);
    arg0K0 = 1;
    goto L33796;}
  else {
    SvalS = new_2054X;
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}}
 L51553: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(len_1462X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(init_1463X, 2)));
  arg0K0 = 2;
  goto L33796;}
 L51578: {
  vector_2055X = arg0K0;
  if ((1 == vector_2055X)) {push_exception_setupB(9, 1);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(len_1462X, 2)));
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(init_1463X, 2)));
    arg0K0 = 2;
    goto L33796;}
  else {
    arg0K0 = (-1 + len_1462X);
    goto L51600;}}
 L64829: {
push_exception_setupB(5, 1);
  x_2056X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2056X);
  arg0K0 = 1;
  goto L33796;}
 L60548: {
push_exception_setupB(8, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1467X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(index_1468X, 2)));
  arg0K0 = 2;
  goto L33796;}
 L64235: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1467X);
  x_2057X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2057X);
  arg0K0 = 2;
  goto L33796;}
 L57752: {
push_exception_setupB(8, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1471X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(index_1472X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(Kchar_1473X, 2)));
  arg0K0 = 3;
  goto L33796;}
 L57731: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1471X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(index_1472X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(Kchar_1473X, 2)));
  arg0K0 = 3;
  goto L33796;}
 L62895: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1471X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1470X);
  x_2058X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2058X);
  arg0K0 = 3;
  goto L33796;}
 L51764: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(len_1476X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(init_1477X, 2)));
  arg0K0 = 2;
  goto L33796;}
 L51789: {
  vector_2059X = arg0K0;
  if ((1 == vector_2059X)) {push_exception_setupB(9, 1);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(len_1476X, 2)));
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(init_1477X, 2)));
    arg0K0 = 2;
    goto L33796;}
  else {
    arg0K0 = (-1 + len_1476X);
    goto L51811;}}
 L51983: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(len_1482X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((9 + (PS_SHIFT_LEFT_INLINE(init_1483X, 8))));
  arg0K0 = 2;
  goto L33796;}
 L52008: {
  vector_2060X = arg0K0;
  if ((1 == vector_2060X)) {push_exception_setupB(9, 1);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(len_1482X, 2)));
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((9 + (PS_SHIFT_LEFT_INLINE(init_1483X, 8))));
    arg0K0 = 2;
    goto L33796;}
  else {
    arg0K0 = (-1 + len_1482X);
    goto L52030;}}
 L60704: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1481X);
  x_2061X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2061X);
  arg0K0 = 2;
  goto L33796;}
 L64879: {
push_exception_setupB(5, 1);
  x_2062X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2062X);
  arg0K0 = 1;
  goto L33796;}
 L60769: {
push_exception_setupB(8, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1488X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(index_1489X, 2)));
  arg0K0 = 2;
  goto L33796;}
 L60797: {
  bits_2063X = arg0K0;
  j_2064X = arg0K1;
  scalar_value_2065X = arg0K2;
  if ((j_2064X < 4)) {
    PS_SHIFT_LEFT((*((unsigned char *) ((((char *) (-3 + arg2_1488X))) + ((PS_SHIFT_LEFT_INLINE(index_1489X, 2)) + j_2064X)))), bits_2063X, x_2066X)
    arg0K0 = (8 + bits_2063X);
    arg0K1 = (1 + j_2064X);
    arg0K2 = (x_2066X + scalar_value_2065X);
    goto L60797;}
  else {
    SvalS = (9 + (PS_SHIFT_LEFT_INLINE(scalar_value_2065X, 8)));
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}}
 L64353: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1488X);
  x_2067X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2067X);
  arg0K0 = 2;
  goto L33796;}
 L57907: {
push_exception_setupB(8, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1492X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(index_1493X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((9 + (PS_SHIFT_LEFT_INLINE(Kchar_1494X, 8))));
  arg0K0 = 3;
  goto L33796;}
 L57971: {
  bits_2068X = arg0K0;
  j_2069X = arg0K1;
  shifted_2070X = arg0K2;
  if ((j_2069X < 4)) {
    *((unsigned char *) ((((char *) (-3 + arg3_1492X))) + ((PS_SHIFT_LEFT_INLINE(index_1493X, 2)) + j_2069X))) = (unsigned char) ((255 & shifted_2070X));
    arg0K0 = (8 + bits_2068X);
    arg0K1 = (1 + j_2069X);
    arg0K2 = (PS_SHIFT_RIGHT_LOGICAL_INLINE(shifted_2070X, 8));
    goto L57971;}
  else {
    SvalS = 13;
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}}
 L57886: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1492X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(index_1493X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((9 + (PS_SHIFT_LEFT_INLINE(Kchar_1494X, 8))));
  arg0K0 = 3;
  goto L33796;}
 L63025: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1492X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1491X);
  x_2071X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2071X);
  arg0K0 = 3;
  goto L33796;}
 L40710: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg5_1499X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(from_index_1500X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1497X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(to_index_1501X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(count_1502X, 2)));
  arg0K0 = 5;
  goto L33796;}
 L46607: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg5_1499X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg4_1498X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1497X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1496X);
  x_2072X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2072X);
  arg0K0 = 5;
  goto L33796;}
 L30760: {
  bucket_2073X = arg0K0;
  arg0K0 = bucket_2073X;
  goto L30766;}
 L47811: {
push_exception_setupB(5, 1);
  x_2074X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2074X);
  arg0K0 = 1;
  goto L33796;}
 L62581: {
  val_2075X = arg0K0;
  SvalS = val_2075X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L62562: {
push_exception_setupB(5, 1);
  x_2076X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2076X);
  arg0K0 = 1;
  goto L33796;}
 L57509: {
  if ((1 == (SvalS))) {
    addr_2077X = (((char *) (-3 + arg2_1514X))) + 8;S48_WRITE_BARRIER(arg2_1514X, addr_2077X, 273);
    *((long *) addr_2077X) = (long) (273);
    goto L57515;}
  else {
    if ((17 == (255 & (*((long *) ((((char *) (-3 + arg2_1514X))) + 8)))))) {
      addr_2078X = (((char *) (-3 + arg2_1514X))) + 8;S48_WRITE_BARRIER(arg2_1514X, addr_2078X, 529);
      *((long *) addr_2078X) = (long) (529);
      goto L57515;}
    else {
      goto L57515;}}}
 L57516: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1514X);
  x_2079X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2079X);
  arg0K0 = 2;
  goto L33796;}
 L67858: {
  val_2080X = arg0K0;
  SvalS = val_2080X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L67871: {
  SvalS = x_1517X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L52434: {
  if ((0 == (3 & arg4_1520X))) {
    if (((PS_SHIFT_RIGHT_INLINE(arg4_1520X, 2)) < 0)) {push_exception_setupB(5, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (arg4_1520X);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(mode_1521X, 2)));
      arg0K0 = 2;
      goto L33796;}
    else {
      arg0K0 = (PS_SHIFT_RIGHT_INLINE(arg4_1520X, 2));
      goto L52220;}}
  else {
    if ((3 == (3 & arg4_1520X))) {
      if ((17 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg4_1520X))))), 2))))) {
        filename_2081X = ((char *)(((char *) (-3 + arg4_1520X))));
        if ((1 == mode_1521X)) {
          goto L52282;}
        else {
          if ((3 == mode_1521X)) {
            goto L52282;}
          else {
            v_2082X = ps_open_fd(filename_2081X, 0, &v_2083X);
            arg0K0 = v_2082X;
            arg0K1 = v_2083X;
            goto L52291;}}}
      else {push_exception_setupB(5, 1);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg4_1520X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(mode_1521X, 2)));
        arg0K0 = 2;
        goto L33796;}}
    else {push_exception_setupB(5, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (arg4_1520X);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(mode_1521X, 2)));
      arg0K0 = 2;
      goto L33796;}}}
 L67888: {
push_exception_setupB(5, 1);
  x_2084X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2084X);
  arg0K0 = 1;
  goto L33796;}
 L61061: {
  if ((1 == (SvalS))) {
    arg4K0 = 0;
    goto L61071;}
  else {
    arg4K0 = 1;
    goto L61071;}}
 L61072: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg5_1530X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg4_1529X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1528X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1527X);
  x_2085X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2085X);
  arg0K0 = 5;
  goto L33796;}
 L53067: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg4_1534X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1533X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(start_1535X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(count_1536X, 2)));
  arg0K0 = 4;
  goto L33796;}
 L53066: {
  val_2086X = arg0K0;
  SvalS = val_2086X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L61275: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg4_1534X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1533X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1532X);
  x_2087X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2087X);
  arg0K0 = 4;
  goto L33796;}
 L64050: {
  val_2088X = arg0K0;
  SvalS = val_2088X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L57062: {
  val_2089X = arg0K0;
  SvalS = val_2089X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L67921: {
push_exception_setupB(5, 1);
  x_2090X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2090X);
  arg0K0 = 1;
  goto L33796;}
 L61423: {
  val_2091X = arg0K0;
  SvalS = val_2091X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L17657: {
  x_2092X = Spending_channels_headS;
  if ((1 == x_2092X)) {
    Spending_interruptsS = (-17 & (Spending_interruptsS));
    goto L17669;}
  else {
    goto L17669;}}
 L17675: {
  ch_2093X = arg0K0;
  prev_2094X = arg0K1;
  if ((1 == ch_2093X)) {
    addr_2095X = (((char *) (-3 + channel_1553X))) + 40;S48_WRITE_BARRIER(channel_1553X, addr_2095X, 1);
    *((long *) addr_2095X) = (long) (1);
    n_2096X = ps_abort_fd_op((PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + channel_1553X))) + 16))), 2)));
    arg0K0 = (PS_SHIFT_LEFT_INLINE(n_2096X, 2));
    goto L61423;}
  else {
    if ((ch_2093X == channel_1553X)) {
      y_2097X = Spending_channels_tailS;
      if ((ch_2093X == y_2097X)) {
        Spending_channels_tailS = prev_2094X;
        goto L17699;}
      else {
        goto L17699;}}
    else {
      arg0K0 = (*((long *) ((((char *) (-3 + ch_2093X))) + 32)));
      arg0K1 = ch_2093X;
      goto L17675;}}}
 L61406: {
push_exception_setupB(5, 1);
  x_2098X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2098X);
  arg0K0 = 1;
  goto L33796;}
 L24789: {
  i_2099X = arg0K0;
  res_2100X = arg0K1;
  if ((-1 == i_2099X)) {
    SvalS = res_2100X;
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}
  else {
    channel_2101X = *((Svm_channelsS) + i_2099X);
    if ((3 == (3 & channel_2101X))) {
      if ((6 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + channel_2101X))))), 2))))) {
        addr_2102X = s48_allocate_small(24);
        *((long *) addr_2102X) = (long) (4098);
        x_2103X = 3 + (((long) (addr_2102X + 8)));
        *((long *) (((char *) (-3 + x_2103X)))) = (long) (channel_2101X);
        *((long *) ((((char *) (-3 + x_2103X))) + 8)) = (long) (res_2100X);
        arg0K0 = x_2103X;
        goto L24803;}
      else {
        arg0K0 = res_2100X;
        goto L24803;}}
    else {
      arg0K0 = res_2100X;
      goto L24803;}}}
 L53288: {
  old_2104X = *((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24));
  if ((1 == old_2104X)) {
    goto L53304;}
  else {
    addr_2105X = ((char *) (-3 + old_2104X));S48_WRITE_BARRIER(old_2104X, addr_2105X, 1);
    *((long *) addr_2105X) = (long) (1);
    goto L53304;}}
 L53319: {
  if ((proposal_1562X == (*((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24))))) {
    SvalS = 13;
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}
  else {push_exception_setupB(5, 1);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (proposal_1562X);
    arg0K0 = 1;
    goto L33796;}}
 L14777: {
  i_2106X = arg0K0;
  stob_2107X = *((long *) ((((char *) (-3 + log_1564X))) + (PS_SHIFT_LEFT_INLINE(i_2106X, 3))));
  if ((1 == stob_2107X)) {
    log_2108X = *((long *) ((((char *) (-3 + proposal_1563X))) + 16));
    arg0K0 = 0;
    goto L15015;}
  else {
    value_2109X = *((long *) ((((char *) (-3 + log_1564X))) + (16 + (PS_SHIFT_LEFT_INLINE(i_2106X, 3)))));
    verify_2110X = *((long *) ((((char *) (-3 + log_1564X))) + (24 + (PS_SHIFT_LEFT_INLINE(i_2106X, 3)))));
    if ((29 == verify_2110X)) {
      if ((3 == (3 & stob_2107X))) {
        if ((0 == (128 & (*((long *) (((char *) (-11 + stob_2107X)))))))) {
          goto L14829;}
        else {
          goto L53567;}}
      else {
        goto L53567;}}
    else {
      if ((verify_2110X == (*((long *) ((((char *) (-3 + stob_2107X))) + (PS_SHIFT_LEFT_INLINE((-4 & (*((long *) ((((char *) (-3 + log_1564X))) + (8 + (PS_SHIFT_LEFT_INLINE(i_2106X, 3))))))), 1))))))) {
        if ((verify_2110X == value_2109X)) {
          goto L14829;}
        else {
          if ((3 == (3 & stob_2107X))) {
            if ((0 == (128 & (*((long *) (((char *) (-11 + stob_2107X)))))))) {
              goto L14829;}
            else {
              goto L53567;}}
          else {
            goto L53567;}}}
      else {
        goto L53567;}}}}
 L40994: {
  value_2111X = arg0K0;
  SvalS = value_2111X;
  Scode_pointerS = ((Scode_pointerS) + 3);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L40995: {
push_exception_setupB(5, 3);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (stob_1565X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(type_1566X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(offset_1567X, 2)));
  arg0K0 = 3;
  goto L33796;}
 L41088: {
push_exception_setupB(5, 2);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg5_1573X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(from_index_1574X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1571X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(to_index_1575X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(count_1576X, 2)));
  arg0K0 = 5;
  goto L33796;}
 L41164: {
  memmove((void *)((((char *) (-3 + arg3_1571X))) + to_index_1575X), (void *)((((char *) (-3 + arg5_1573X))) + from_index_1574X),count_1576X);
  SvalS = 13;
  Scode_pointerS = ((Scode_pointerS) + 2);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L41307: {
  left_2112X = arg0K0;
  copies_2113X = arg0K1;
  if ((1 == copies_2113X)) {
    if ((left_2112X < count_1576X)) {
      goto L41088;}
    else {
      from_index_2114X = PS_SHIFT_LEFT_INLINE(from_index_1574X, 2);
      to_index_2115X = PS_SHIFT_LEFT_INLINE(to_index_1575X, 2);
      count_2116X = PS_SHIFT_LEFT_INLINE(count_1576X, 2);
      Stemp0S = arg5_1573X;
      Stemp1S = arg3_1571X;
      addr_2117X = s48_allocate_tracedAgc(56);
      if ((addr_2117X == NULL)) {
        arg0K0 = 1;
        goto L16469;}
      else {
        *((long *) addr_2117X) = (long) (12298);
        arg0K0 = (3 + (((long) (addr_2117X + 8))));
        goto L16469;}}}
  else {
    arg0K0 = (left_2112X - (PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + copies_2113X))) + 32))), 2)));
    arg0K1 = (*((long *) ((((char *) (-3 + copies_2113X))) + 40)));
    goto L41307;}}
 L41132: {
push_exception_setupB(6, 2);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg5_1573X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(from_index_1574X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1571X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(to_index_1575X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(count_1576X, 2)));
  arg0K0 = 5;
  goto L33796;}
 L46873: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg5_1573X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg4_1572X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1571X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1570X);
  x_2118X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2118X);
  arg0K0 = 5;
  goto L33796;}
 L41534: {
push_exception_setupB(8, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1578X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(index_1579X, 2)));
  arg0K0 = 2;
  goto L33796;}
 L41533: {
  value_2119X = arg0K0;
  SvalS = value_2119X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L24530: {
  i_2120X = arg0K0;
  next_stob_2121X = *((long *) ((((char *) (-3 + log_1583X))) + (PS_SHIFT_LEFT_INLINE(i_2120X, 3))));
  if ((1 == next_stob_2121X)) {
    v_2122X = add_log_entryAgc(2, i_2120X, arg2_1578X, index_1582X, (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((((char *) (-3 + arg2_1578X))) + (PS_SHIFT_RIGHT_INLINE(index_1582X, 2))))), 2)), 1);
    arg0K0 = v_2122X;
    goto L41533;}
  else {
    if ((arg2_1578X == next_stob_2121X)) {
      if ((index_1582X == (*((long *) ((((char *) (-3 + log_1583X))) + (8 + (PS_SHIFT_LEFT_INLINE(i_2120X, 3)))))))) {
        arg0K0 = (*((long *) ((((char *) (-3 + log_1583X))) + (16 + (PS_SHIFT_LEFT_INLINE(i_2120X, 3))))));
        goto L41533;}
      else {
        goto L24552;}}
    else {
      goto L24552;}}}
 L47069: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1578X);
  x_2123X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2123X);
  arg0K0 = 2;
  goto L33796;}
 L41664: {
push_exception_setupB(8, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1585X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(index_1586X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (byte_1587X);
  arg0K0 = 3;
  goto L33796;}
 L41663: {
  SvalS = 13;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L24706: {
  i_2124X = arg0K0;
  next_stob_2125X = *((long *) ((((char *) (-3 + log_1591X))) + (PS_SHIFT_LEFT_INLINE(i_2124X, 3))));
  if ((1 == next_stob_2125X)) {add_log_entryAgc(2, i_2124X, arg3_1585X, index_1590X, byte_1587X, 0);
    goto L41663;}
  else {
    if ((arg3_1585X == next_stob_2125X)) {
      if ((index_1590X == (*((long *) ((((char *) (-3 + log_1591X))) + (8 + (PS_SHIFT_LEFT_INLINE(i_2124X, 3)))))))) {
        addr_2126X = (((char *) (-3 + log_1591X))) + (16 + (PS_SHIFT_LEFT_INLINE(i_2124X, 3)));S48_WRITE_BARRIER(log_1591X, addr_2126X, byte_1587X);
        *((long *) addr_2126X) = (long) (byte_1587X);
        goto L41663;}
      else {
        goto L24726;}}
    else {
      goto L24726;}}}
 L41613: {
push_exception_setupB(6, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1585X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(index_1586X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (byte_1587X);
  arg0K0 = 3;
  goto L33796;}
 L47174: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1585X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1584X);
  x_2127X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2127X);
  arg0K0 = 3;
  goto L33796;}
 L58140: {
  status_2128X = arg0K0;push_exception_setupB(25, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(status_2128X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg4_1595X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1594X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1593X);
  arg0K0 = 4;
  goto L33796;}
 L63210: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg4_1595X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1594X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1593X);
  x_2129X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2129X);
  arg0K0 = 4;
  goto L33796;}
 L63918: {
push_exception_setupB(5, 1);
  x_2130X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2130X);
  arg0K0 = 1;
  goto L33796;}
 L58396: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1607X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (proc_1608X);
  arg0K0 = 2;
  goto L33796;}
 L61542: {
  firstP_2131X = arg4K0;
  vector_2132X = s48_find_all(type_1622X);
  if ((1 == vector_2132X)) {
    if (firstP_2131X) {s48_collect(1);
      arg4K0 = 0;
      goto L61542;}
    else {push_exception_setupB(9, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(type_1622X, 2)));
      arg0K0 = 1;
      goto L33796;}}
  else {
    SvalS = vector_2132X;
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}}
 L68041: {
  firstP_2133X = arg4K0;
  type_2134X = arg0K1;
  vector_2135X = s48_find_all_records(type_2134X);
  if ((1 == vector_2135X)) {
    if (firstP_2133X) {
      Stemp0S = type_2134X;s48_collect(1);
      value_2136X = Stemp0S;
      Stemp0S = 1;
      arg4K0 = 0;
      arg0K1 = value_2136X;
      goto L68041;}
    else {push_exception_setupB(9, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (type_2134X);
      arg0K0 = 1;
      goto L33796;}}
  else {
    SvalS = vector_2135X;
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}}
 L37998: {
push_exception_setupB(5, 1);
  x_2137X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2137X);
  arg0K0 = 1;
  goto L33796;}
 L36319: {
  Slast_code_calledS = code_1629X;
  Scode_pointerS = ((((char *) (-3 + code_1629X))) + (pc_1632X + (PS_SHIFT_RIGHT_INLINE(size_1631X, 2))));
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L34059: {
  ps_write_string("returning to nc ", (stderr));
  ps_write_integer((*((long *) (SstackS))), (stderr));
  arg0K0 = 0;
  arg0K1 = 25;
  arg0K2 = 0;
  goto L33224;}
 L36888: {
push_exception_setupB(5, 1);
  x_2138X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2138X);
  arg0K0 = 1;
  goto L33796;}
 L68089: {
  SvalS = (PS_SHIFT_LEFT_INLINE(old_1641X, 2));
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L65044: {
  x_2139X = s48_schedule_alarm_interrupt((PS_SHIFT_RIGHT_INLINE(p_1653X, 2)));
  SvalS = (PS_SHIFT_LEFT_INLINE(x_2139X, 2));
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L62774: {
  if ((1 == (SvalS))) {
    arg4K0 = 0;
    goto L62778;}
  else {
    arg4K0 = 1;
    goto L62778;}}
 L62779: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1655X);
  x_2140X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2140X);
  arg0K0 = 2;
  goto L33796;}
 L41875: {
  rest_list_2141X = arg0K0;
  if ((25 == rest_list_2141X)) {
    name_2142X = *((long *) ((SstackS) + (-16 + (PS_SHIFT_LEFT_INLINE(nargs_1658X, 3)))));
    proc_2143X = *((long *) ((SstackS) + (-8 + (PS_SHIFT_LEFT_INLINE(nargs_1658X, 3)))));
    args_2144X = SstackS;
    if ((3 == (3 & name_2142X))) {
      if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + name_2142X))))), 2))))) {
        if ((3 == (3 & proc_2143X))) {
          if ((17 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + proc_2143X))))), 2))))) {
            if ((8 == (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + proc_2143X))))), 8)))) {
              SstackS = (ScontS);
              result_2145X = s48_external_call(proc_2143X, name_2142X, (-2 + nargs_1658X), args_2144X);
              if ((Sexternal_exceptionPS)) {
                Sexternal_exceptionPS = 0;
                arg0K0 = (Sexternal_exception_nargsS);
                goto L33796;}
              else {
                SvalS = result_2145X;
                Scode_pointerS = ((Scode_pointerS) + 1);
                arg3K0 = (Scode_pointerS);
                goto L36237;}}
            else {
              goto L42131;}}
          else {
            goto L42131;}}
        else {
          goto L42131;}}
      else {
        goto L42131;}}
    else {
      goto L42131;}}
  else {
    x_2146X = *((long *) (((char *) (-3 + rest_list_2141X))));
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (x_2146X);
    arg0K0 = (*((long *) ((((char *) (-3 + rest_list_2141X))) + 8)));
    goto L41875;}}
 L42176: {
  rest_list_2147X = arg0K0;
  if ((25 == rest_list_2147X)) {
    name_2148X = *((long *) ((SstackS) + (-16 + (PS_SHIFT_LEFT_INLINE(nargs_1663X, 3)))));
    proc_2149X = *((long *) ((SstackS) + (-8 + (PS_SHIFT_LEFT_INLINE(nargs_1663X, 3)))));
    args_2150X = SstackS;
    if ((3 == (3 & name_2148X))) {
      if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + name_2148X))))), 2))))) {
        if ((3 == (3 & proc_2149X))) {
          if ((17 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + proc_2149X))))), 2))))) {
            if ((8 == (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + proc_2149X))))), 8)))) {
              SstackS = (ScontS);
              result_2151X = s48_external_call_2(proc_2149X, name_2148X, (-2 + nargs_1663X), args_2150X);
              if ((Sexternal_exceptionPS)) {
                Sexternal_exceptionPS = 0;
                arg0K0 = (Sexternal_exception_nargsS);
                goto L33796;}
              else {
                SvalS = result_2151X;
                Scode_pointerS = ((Scode_pointerS) + 1);
                arg3K0 = (Scode_pointerS);
                goto L36237;}}
            else {
              goto L42432;}}
          else {
            goto L42432;}}
        else {
          goto L42432;}}
      else {
        goto L42432;}}
    else {
      goto L42432;}}
  else {
    x_2152X = *((long *) (((char *) (-3 + rest_list_2147X))));
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (x_2152X);
    arg0K0 = (*((long *) ((((char *) (-3 + rest_list_2147X))) + 8)));
    goto L42176;}}
 L61637: {
  if ((1 == (SvalS))) {
    v_2153X = Hlookup853((Sexported_bindingsS), arg2_1667X, 0);
    arg0K0 = v_2153X;
    goto L61678;}
  else {
    v_2154X = Hlookup834((Simported_bindingsS), arg2_1667X, 0);
    arg0K0 = v_2154X;
    goto L61678;}}
 L61642: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1667X);
  x_2155X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2155X);
  arg0K0 = 2;
  goto L33796;}
 L46020: {
  if ((1 == (SvalS))) {
    arg0K0 = (Sexported_bindingsS);
    goto L46055;}
  else {
    arg0K0 = (Simported_bindingsS);
    goto L46055;}}
 L46025: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1669X);
  x_2156X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2156X);
  arg0K0 = 2;
  goto L33796;}
 L68151: {
  firstP_2157X = arg4K0;
  vector_2158X = s48_gather_objects(shared_binding_undefinedP, for_each_imported_binding);
  if ((1 == vector_2158X)) {
    if (firstP_2157X) {s48_collect(1);
      arg4K0 = 0;
      goto L68151;}
    else {push_exception_setupB(9, 1);
      arg0K0 = 0;
      goto L33796;}}
  else {
    SvalS = vector_2158X;
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}}
 L65352: {
  x_2159X = arg0K0;
  SvalS = (PS_SHIFT_LEFT_INLINE(x_2159X, 2));
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L65353: {
  if ((1 == arg_1671X)) {
#ifdef USE_DIRECT_THREADING
    unused_event_type_uid_return_address = &&unused_event_type_uid_return_1;
#else
    unused_event_type_uid_return_tag = 1;
#endif
    goto unused_event_type_uid;
   unused_event_type_uid_return_1:
    uid_2160X = unused_event_type_uid0_return_value;
    if ((-1 == uid_2160X)) {
      arg0K0 = uid_2160X;
      goto L65358;}
    else {
      merged_arg0K0 = uid_2160X;
#ifdef USE_DIRECT_THREADING
      use_event_type_uidB_return_address = &&use_event_type_uidB_return_3;
#else
      use_event_type_uidB_return_tag = 3;
#endif
      goto use_event_type_uidB;
     use_event_type_uidB_return_3:
      arg0K0 = uid_2160X;
      goto L65358;}}
  else {push_exception_setupB(5, 1);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (arg_1671X);
    arg0K0 = 1;
    goto L33796;}}
 L6577: {
  type_2161X = *((Sevent_typesS) + index_1682X);
  if ((type_2161X->usedP)) {
    if ((NULL == (type_2161X->next))) {
      type_2162X = *((Sevent_typesS) + index_1682X);
      if ((NULL == (type_2162X->next))) {
        type_2162X->next = (Sunused_event_types_headS);
        type_2162X->usedP = 0;
        Sunused_event_types_headS = type_2162X;
        goto L68179;}
      else {
        ps_write_string("trying to unregister external event that is still in use : ", (stderr));
        ps_write_integer(index_1682X, (stderr));
        { long ignoreXX;
        PS_WRITE_CHAR(10, (stderr), ignoreXX) }
        ps_error("assertion violation", 0);
        goto L68179;}}
    else {
      ps_write_string("trying to unregister external event that is still in use : ", (stderr));
      ps_write_integer(index_1682X, (stderr));
      { long ignoreXX;
      PS_WRITE_CHAR(10, (stderr), ignoreXX) }
      ps_error("assertion violation", 0);
      goto L68179;}}
  else {
    ps_write_string("trying to unregister invalid external event: ", (stderr));
    ps_write_integer(index_1682X, (stderr));
    { long ignoreXX;
    PS_WRITE_CHAR(10, (stderr), ignoreXX) }
    ps_error("assertion violation", 0);
    goto L68179;}}
 L63852: {
  option_2163X = arg0K0;
  seconds_2164X = arg0K1;
  mseconds_2165X = arg0K2;
  if ((2305843009213692 < seconds_2164X)) {push_exception_setupB(7, 1);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(option_2163X, 2)));
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(seconds_2164X, 2)));
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(mseconds_2165X, 2)));
    arg0K0 = 3;
    goto L33796;}
  else {
    SvalS = (PS_SHIFT_LEFT_INLINE(((1000 * seconds_2164X) + mseconds_2165X), 2));
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}}
 L68225: {
  s48_Scallback_return_stack_blockS = arg2_1705X;
  arg0K0 = x_1706X;
  goto L70968;}
 L55759: {
  val_2166X = arg0K0;
  SvalS = val_2166X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L55724: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1707X);
  x_2167X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2167X);
  arg0K0 = 2;
  goto L33796;}
 L54157: {
  len_2168X = PS_SHIFT_LEFT_INLINE(n_1712X, 2);
  addr_2169X = s48_allocate_small((8 + len_2168X));
  *((long *) addr_2169X) = (long) ((66 + (PS_SHIFT_LEFT_INLINE(len_2168X, 8))));
  obj_2170X = 3 + (((long) (addr_2169X + 8)));
  arg0K0 = arg2_1711X;
  arg0K1 = (-1 + n_1712X);
  goto L54134;}
 L54109: {
  if ((25 == arg2_1711X)) {
    goto L54157;}
  else {push_exception_setupB(5, 1);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (arg2_1711X);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(n_1712X, 2)));
    arg0K0 = 2;
    goto L33796;}}
 L57125: {
  list_2171X = arg0K0;
  slow_2172X = arg0K1;
  move_slowP_2173X = arg4K2;
  if ((25 == list_2171X)) {
    SvalS = 1;
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}
  else {
    if ((3 == (3 & list_2171X))) {
      if ((0 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + list_2171X))))), 2))))) {
        head_2174X = *((long *) (((char *) (-3 + list_2171X))));
        if ((3 == (3 & head_2174X))) {
          if ((0 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + head_2174X))))), 2))))) {
            if (((*((long *) (((char *) (-3 + head_2174X))))) == arg2_1714X)) {
              SvalS = head_2174X;
              Scode_pointerS = ((Scode_pointerS) + 1);
              arg3K0 = (Scode_pointerS);
              goto L36237;}
            else {
              list_2175X = *((long *) ((((char *) (-3 + list_2171X))) + 8));
              if ((list_2175X == slow_2172X)) {push_exception_setupB(5, 1);
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) (arg2_1714X);
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) (list_1715X);
                arg0K0 = 2;
                goto L33796;}
              else {
                if (move_slowP_2173X) {
                  arg0K0 = list_2175X;
                  arg0K1 = (*((long *) ((((char *) (-3 + slow_2172X))) + 8)));
                  arg4K2 = 0;
                  goto L57125;}
                else {
                  arg0K0 = list_2175X;
                  arg0K1 = slow_2172X;
                  arg4K2 = 1;
                  goto L57125;}}}}
          else {push_exception_setupB(5, 1);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (arg2_1714X);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (list_1715X);
            arg0K0 = 2;
            goto L33796;}}
        else {push_exception_setupB(5, 1);
          SstackS = ((SstackS) + -8);
          *((long *) (SstackS)) = (long) (arg2_1714X);
          SstackS = ((SstackS) + -8);
          *((long *) (SstackS)) = (long) (list_1715X);
          arg0K0 = 2;
          goto L33796;}}
      else {push_exception_setupB(5, 1);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg2_1714X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (list_1715X);
        arg0K0 = 2;
        goto L33796;}}
    else {push_exception_setupB(5, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (arg2_1714X);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (list_1715X);
      arg0K0 = 2;
      goto L33796;}}}
 L55570: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1716X);
  x_2176X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2176X);
  arg0K0 = 2;
  goto L33796;}
 L55611: {
  val_2177X = arg0K0;
  SvalS = val_2177X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L42527: {
  len_2178X = PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg3_1722X))))), 8))), 3);
  if ((index_1723X < 0)) {
    goto L42506;}
  else {
    if ((index_1723X < len_2178X)) {
      v_2179X = *((unsigned char *) ((Scode_pointerS) + 1));
      if ((0 == v_2179X)) {
        goto L42496;}
      else {
        if ((1 == (*((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24))))) {
          goto L42496;}
        else {
          merged_arg0K0 = arg3_1722X;
          merged_arg0K1 = (PS_SHIFT_LEFT_INLINE(index_1723X, 2));
#ifdef USE_DIRECT_THREADING
          proposal_d_read_return_address = &&proposal_d_read_return_2;
#else
          proposal_d_read_return_tag = 2;
#endif
          goto proposal_d_read;
         proposal_d_read_return_2:
          v_2180X = proposal_d_read0_return_value;
          arg0K0 = v_2180X;
          goto L42505;}}}
    else {
      goto L42506;}}}
 L42526: {
push_exception_setupB(5, 2);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1722X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1721X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(index_1723X, 2)));
  arg0K0 = 3;
  goto L33796;}
 L42817: {
  if ((3 == (3 & arg4_1729X))) {
    if ((0 == (128 & (*((long *) (((char *) (-11 + arg4_1729X)))))))) {
      len_2181X = PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg4_1729X))))), 8))), 3);
      if ((index_1730X < 0)) {
        goto L42794;}
      else {
        if ((index_1730X < len_2181X)) {
          v_2182X = *((unsigned char *) ((Scode_pointerS) + 1));
          if ((0 == v_2182X)) {
            goto L42784;}
          else {
            if ((1 == (*((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24))))) {
              goto L42784;}
            else {
              merged_arg0K0 = arg4_1729X;
              merged_arg0K1 = (PS_SHIFT_LEFT_INLINE(index_1730X, 2));
              merged_arg0K2 = value_1731X;
#ifdef USE_DIRECT_THREADING
              proposal_d_write_return_address = &&proposal_d_write_return_2;
#else
              proposal_d_write_return_tag = 2;
#endif
              goto proposal_d_write;
             proposal_d_write_return_2:
              goto L42793;}}}
        else {
          goto L42794;}}}
    else {
      goto L42749;}}
  else {
    goto L42749;}}
 L42816: {
push_exception_setupB(5, 2);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg4_1729X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1728X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(index_1730X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (value_1731X);
  arg0K0 = 4;
  goto L33796;}
 L34431: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(encoding_1739X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((9 + (PS_SHIFT_LEFT_INLINE(value_1740X, 8))));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1736X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(start_1741X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(count_1742X, 2)));
  arg0K0 = 5;
  goto L33796;}
 L34460: {
  encoding_okP_2183X = arg4K0;
  okP_2184X = arg4K1;
  out_of_spaceP_2185X = arg4K2;
  count_2186X = arg0K3;
  if (encoding_okP_2183X) {
    if (okP_2184X) {
      if (out_of_spaceP_2185X) {
        arg0K0 = 1;
        goto L34483;}
      else {
        arg0K0 = 5;
        goto L34483;}}
    else {
      arg0K0 = 1;
      goto L34483;}}
  else {push_exception_setupB(18, 1);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(encoding_1739X, 2)));
    arg0K0 = 1;
    goto L33796;}}
 L35283: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg5_1738X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg4_1737X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1736X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1735X);
  x_2187X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2187X);
  arg0K0 = 5;
  goto L33796;}
 L54312: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(encoding_1757X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((9 + (PS_SHIFT_LEFT_INLINE(value_1758X, 8))));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1754X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(start_1759X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(count_1760X, 2)));
  arg0K0 = 5;
  goto L33796;}
 L54348: {
  SvalS = 13;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L62046: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg5_1756X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg4_1755X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1754X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1753X);
  x_2188X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2188X);
  arg0K0 = 5;
  goto L33796;}
 L34780: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(encoding_1771X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1769X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(start_1772X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(count_1773X, 2)));
  arg0K0 = 4;
  goto L33796;}
 L34806: {
  encoding_okP_2189X = arg4K0;
  okP_2190X = arg4K1;
  incompleteP_2191X = arg4K2;
  value_2192X = arg0K3;
  count_2193X = arg0K4;
  if (encoding_okP_2189X) {
    if (okP_2190X) {
      if (incompleteP_2191X) {
        arg0K0 = 1;
        goto L34846;}
      else {
        arg0K0 = (9 + (PS_SHIFT_LEFT_INLINE(value_2192X, 8)));
        goto L34846;}}
    else {
      arg0K0 = 1;
      goto L34846;}}
  else {push_exception_setupB(18, 1);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(encoding_1771X, 2)));
    arg0K0 = 1;
    goto L33796;}}
 L35479: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg4_1770X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1769X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1768X);
  x_2194X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2194X);
  arg0K0 = 4;
  goto L33796;}
 L54766: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(encoding_1792X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1790X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(start_1793X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(count_1794X, 2)));
  arg0K0 = 4;
  goto L33796;}
 L54919: {
  SvalS = 13;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L62242: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg4_1791X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1790X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1789X);
  x_2195X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2195X);
  arg0K0 = 4;
  goto L33796;}
 L43098: {
  port_2196X = arg0K0;
  if ((3 == (3 & port_2196X))) {
    if ((7 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + port_2196X))))), 2))))) {
      if ((0 == (4 & (PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + port_2196X))) + 24))), 2))))) {
        goto L43155;}
      else {
        b_2197X = *((long *) ((((char *) (-3 + port_2196X))) + 48));
        if ((1 == b_2197X)) {push_exception_setupB(14, 2);
          SstackS = ((SstackS) + -8);
          *((long *) (SstackS)) = (long) (port_2196X);
          arg0K0 = 1;
          goto L33796;}
        else {
          p_2198X = *((long *) ((((char *) (-3 + port_2196X))) + 56));
          p_2199X = *((long *) ((((char *) (-3 + port_2196X))) + 64));
          i_2200X = PS_SHIFT_RIGHT_INLINE(p_2198X, 2);
          if ((i_2200X == (PS_SHIFT_RIGHT_INLINE(p_2199X, 2)))) {push_exception_setupB(14, 2);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (port_2196X);
            arg0K0 = 1;
            goto L33796;}
          else {
            val_2201X = 4 + (PS_SHIFT_LEFT_INLINE(i_2200X, 2));
            addr_2202X = (((char *) (-3 + port_2196X))) + 56;S48_WRITE_BARRIER(port_2196X, addr_2202X, val_2201X);
            *((long *) addr_2202X) = (long) (val_2201X);
            SvalS = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((((char *) (-3 + b_2197X))) + i_2200X))), 2));
            Scode_pointerS = ((Scode_pointerS) + 2);
            arg3K0 = (Scode_pointerS);
            goto L36237;}}}}
    else {
      goto L43155;}}
  else {
    goto L43155;}}
 L43300: {
  port_2203X = arg0K0;
  if ((3 == (3 & port_2203X))) {
    if ((7 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + port_2203X))))), 2))))) {
      if ((0 == (4 & (PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + port_2203X))) + 24))), 2))))) {
        goto L43357;}
      else {
        b_2204X = *((long *) ((((char *) (-3 + port_2203X))) + 48));
        if ((1 == b_2204X)) {push_exception_setupB(14, 2);
          SstackS = ((SstackS) + -8);
          *((long *) (SstackS)) = (long) (port_2203X);
          arg0K0 = 1;
          goto L33796;}
        else {
          p_2205X = *((long *) ((((char *) (-3 + port_2203X))) + 56));
          p_2206X = *((long *) ((((char *) (-3 + port_2203X))) + 64));
          i_2207X = PS_SHIFT_RIGHT_INLINE(p_2205X, 2);
          if ((i_2207X == (PS_SHIFT_RIGHT_INLINE(p_2206X, 2)))) {push_exception_setupB(14, 2);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (port_2203X);
            arg0K0 = 1;
            goto L33796;}
          else {
            SvalS = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((((char *) (-3 + b_2204X))) + i_2207X))), 2));
            Scode_pointerS = ((Scode_pointerS) + 2);
            arg3K0 = (Scode_pointerS);
            goto L36237;}}}}
    else {
      goto L43357;}}
  else {
    goto L43357;}}
 L43495: {
  byte_2208X = arg0K0;
  port_2209X = arg0K1;
  if ((0 == (3 & byte_2208X))) {
    if ((3 == (3 & port_2209X))) {
      if ((7 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + port_2209X))))), 2))))) {
        if ((0 == (8 & (PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + port_2209X))) + 24))), 2))))) {
          goto L43572;}
        else {
          if ((1 == (*((long *) ((((char *) (-3 + port_2209X))) + 64))))) {push_exception_setupB(14, 2);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (byte_2208X);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (port_2209X);
            arg0K0 = 2;
            goto L33796;}
          else {
            p_2210X = *((long *) ((((char *) (-3 + port_2209X))) + 56));
            b_2211X = *((long *) ((((char *) (-3 + port_2209X))) + 48));
            i_2212X = PS_SHIFT_RIGHT_INLINE(p_2210X, 2);
            if ((i_2212X == (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + b_2211X))))), 8)))) {push_exception_setupB(14, 2);
              SstackS = ((SstackS) + -8);
              *((long *) (SstackS)) = (long) (byte_2208X);
              SstackS = ((SstackS) + -8);
              *((long *) (SstackS)) = (long) (port_2209X);
              arg0K0 = 2;
              goto L33796;}
            else {
              val_2213X = 4 + (PS_SHIFT_LEFT_INLINE(i_2212X, 2));
              addr_2214X = (((char *) (-3 + port_2209X))) + 56;S48_WRITE_BARRIER(port_2209X, addr_2214X, val_2213X);
              *((long *) addr_2214X) = (long) (val_2213X);
              *((unsigned char *) ((((char *) (-3 + b_2211X))) + i_2212X)) = (unsigned char) ((PS_SHIFT_RIGHT_INLINE(byte_2208X, 2)));
              SvalS = 13;
              Scode_pointerS = ((Scode_pointerS) + 2);
              arg3K0 = (Scode_pointerS);
              goto L36237;}}}}
      else {
        goto L43572;}}
    else {
      goto L43572;}}
  else {
    goto L43572;}}
 L43764: {
  port_2215X = arg0K0;
  if ((3 == (3 & port_2215X))) {
    if ((7 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + port_2215X))))), 2))))) {
      if ((0 == (4 & (PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + port_2215X))) + 24))), 2))))) {
        goto L43937;}
      else {
        b_2216X = *((long *) ((((char *) (-3 + port_2215X))) + 48));
        if ((1 == b_2216X)) {push_exception_setupB(14, 2);
          SstackS = ((SstackS) + -8);
          *((long *) (SstackS)) = (long) (port_2215X);
          arg0K0 = 1;
          goto L33796;}
        else {
          arg0K0 = (PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + port_2215X))) + 56))), 2));
          goto L43793;}}}
    else {
      goto L43937;}}
  else {
    goto L43937;}}
 L44412: {
  port_2217X = arg0K0;
  if ((3 == (3 & port_2217X))) {
    if ((7 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + port_2217X))))), 2))))) {
      if ((0 == (4 & (PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + port_2217X))) + 24))), 2))))) {
        goto L44585;}
      else {
        b_2218X = *((long *) ((((char *) (-3 + port_2217X))) + 48));
        if ((1 == b_2218X)) {push_exception_setupB(14, 2);
          SstackS = ((SstackS) + -8);
          *((long *) (SstackS)) = (long) (port_2217X);
          arg0K0 = 1;
          goto L33796;}
        else {
          arg0K0 = (PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + port_2217X))) + 56))), 2));
          goto L44441;}}}
    else {
      goto L44585;}}
  else {
    goto L44585;}}
 L44981: {
  Kchar_2219X = arg0K0;
  port_2220X = arg0K1;
  if ((9 == (255 & Kchar_2219X))) {
    if ((3 == (3 & port_2220X))) {
      if ((7 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + port_2220X))))), 2))))) {
        if ((0 == (8 & (PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + port_2220X))) + 24))), 2))))) {
          goto L45200;}
        else {
          if ((1 == (*((long *) ((((char *) (-3 + port_2220X))) + 64))))) {push_exception_setupB(14, 2);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (Kchar_2219X);
            SstackS = ((SstackS) + -8);
            *((long *) (SstackS)) = (long) (port_2220X);
            arg0K0 = 2;
            goto L33796;}
          else {
            codec_2221X = *((long *) ((((char *) (-3 + port_2220X))) + 8));
            if ((0 == (3 & codec_2221X))) {
              b_2222X = *((long *) ((((char *) (-3 + port_2220X))) + 48));
              i_2223X = PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + port_2220X))) + 56))), 2);
              l_2224X = PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + b_2222X))))), 8);
              if ((i_2223X == l_2224X)) {push_exception_setupB(14, 2);
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) (Kchar_2219X);
                SstackS = ((SstackS) + -8);
                *((long *) (SstackS)) = (long) (port_2220X);
                arg0K0 = 2;
                goto L33796;}
              else {
                x_2225X = *((long *) ((((char *) (-3 + port_2220X))) + 16));
                if ((1 == x_2225X)) {
                  goto L45146;}
                else {
                  if ((10 == (PS_SHIFT_RIGHT_INLINE(Kchar_2219X, 8)))) {
                    encoding_2226X = PS_SHIFT_RIGHT_INLINE(codec_2221X, 2);
                    buffer_2227X = (((char *) (-3 + b_2222X))) + i_2223X;
                    count_2228X = l_2224X - i_2223X;
                    if ((0 == encoding_2226X)) {
                      if ((count_2228X < 1)) {
                        arg4K0 = 1;
                        arg4K1 = 1;
                        arg4K2 = 1;
                        arg0K3 = 1;
                        goto L45081;}
                      else {
                        *((unsigned char *) buffer_2227X) = (unsigned char) (13);
                        arg4K0 = 1;
                        arg4K1 = 1;
                        arg4K2 = 0;
                        arg0K3 = 1;
                        goto L45081;}}
                    else {
                      if ((1 == encoding_2226X)) {
                        if ((count_2228X < 1)) {
                          arg4K0 = 1;
                          arg4K1 = 1;
                          arg4K2 = 1;
                          arg0K3 = 1;
                          goto L45081;}
                        else {
                          *((unsigned char *) buffer_2227X) = (unsigned char) (13);
                          arg4K0 = 1;
                          arg4K1 = 1;
                          arg4K2 = 0;
                          arg0K3 = 1;
                          goto L45081;}}
                      else {
                        if ((2 == encoding_2226X)) {
                          encoding_okP_2229X = encode_scalar_valueUutf_8(13, buffer_2227X, count_2228X, &out_of_spaceP_2230X, &count_2231X);
                          arg4K0 = 1;
                          arg4K1 = encoding_okP_2229X;
                          arg4K2 = out_of_spaceP_2230X;
                          arg0K3 = count_2231X;
                          goto L45081;}
                        else {
                          if ((3 == encoding_2226X)) {
                            encoding_okP_2232X = encode_scalar_valueUutf_16le(13, buffer_2227X, count_2228X, &out_of_spaceP_2233X, &count_2234X);
                            arg4K0 = 1;
                            arg4K1 = encoding_okP_2232X;
                            arg4K2 = out_of_spaceP_2233X;
                            arg0K3 = count_2234X;
                            goto L45081;}
                          else {
                            if ((4 == encoding_2226X)) {
                              encoding_okP_2235X = encode_scalar_valueUutf_16be(13, buffer_2227X, count_2228X, &out_of_spaceP_2236X, &count_2237X);
                              arg4K0 = 1;
                              arg4K1 = encoding_okP_2235X;
                              arg4K2 = out_of_spaceP_2236X;
                              arg0K3 = count_2237X;
                              goto L45081;}
                            else {
                              if ((5 == encoding_2226X)) {
                                if ((count_2228X < 4)) {
                                  arg4K0 = 1;
                                  arg4K1 = 1;
                                  arg4K2 = 1;
                                  arg0K3 = 4;
                                  goto L45081;}
                                else {
                                  *((unsigned char *) buffer_2227X) = (unsigned char) (13);
                                  *((unsigned char *) (buffer_2227X + 1)) = (unsigned char) (0);
                                  *((unsigned char *) (buffer_2227X + 2)) = (unsigned char) (0);
                                  *((unsigned char *) (buffer_2227X + 3)) = (unsigned char) (218103808);
                                  arg4K0 = 1;
                                  arg4K1 = 1;
                                  arg4K2 = 0;
                                  arg0K3 = 4;
                                  goto L45081;}}
                              else {
                                if ((6 == encoding_2226X)) {
                                  if ((count_2228X < 4)) {
                                    arg4K0 = 1;
                                    arg4K1 = 1;
                                    arg4K2 = 1;
                                    arg0K3 = 4;
                                    goto L45081;}
                                  else {
                                    *((unsigned char *) buffer_2227X) = (unsigned char) (218103808);
                                    *((unsigned char *) (buffer_2227X + 1)) = (unsigned char) (0);
                                    *((unsigned char *) (buffer_2227X + 2)) = (unsigned char) (0);
                                    *((unsigned char *) (buffer_2227X + 3)) = (unsigned char) (13);
                                    arg4K0 = 1;
                                    arg4K1 = 1;
                                    arg4K2 = 0;
                                    arg0K3 = 4;
                                    goto L45081;}}
                                else {
                                  arg4K0 = 0;
                                  arg4K1 = 0;
                                  arg4K2 = 0;
                                  arg0K3 = 0;
                                  goto L45081;}}}}}}}}
                  else {
                    goto L45146;}}}}
            else {push_exception_setupB(14, 2);
              SstackS = ((SstackS) + -8);
              *((long *) (SstackS)) = (long) (Kchar_2219X);
              SstackS = ((SstackS) + -8);
              *((long *) (SstackS)) = (long) (port_2220X);
              arg0K0 = 2;
              goto L33796;}}}}
      else {
        goto L45200;}}
    else {
      goto L45200;}}
  else {
    goto L45200;}}
 L55249: {
  vector_2238X = arg0K0;
  if ((1 == vector_2238X)) {push_exception_setupB(9, 1);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(len_1822X, 2)));
    arg0K0 = 1;
    goto L33796;}
  else {
    arg0K0 = 0;
    goto L55265;}}
 L57378: {
  stuff_2239X = arg0K0;
  if ((3 == (3 & stuff_2239X))) {
    if ((0 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + stuff_2239X))))), 2))))) {message_element((*((long *) (((char *) (-3 + stuff_2239X))))), out_1826X);
      arg0K0 = (*((long *) ((((char *) (-3 + stuff_2239X))) + 8)));
      goto L57378;}
    else {
      goto L57369;}}
  else {
    goto L57369;}}
 L32828: {
  arg_count_2240X = arg0K0;
  if ((3 == (3 & handlers_1829X))) {
    if ((2 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + handlers_1829X))))), 2))))) {
      goto L32842;}
    else {
      goto L32884;}}
  else {
    goto L32884;}}
 L17869: {
  x_2241X = Sfinalize_theseS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2241X);
  Sfinalize_theseS = 25;
  n_2242X = Senabled_interruptsS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(n_2242X, 2)));
  if ((Sgc_in_troublePS)) {
    arg0K0 = 5;
    goto L17880;}
  else {
    arg0K0 = 1;
    goto L17880;}}
 L17886: {
  channel_2243X = arg0K0;
  x_2244X = 1 == (Spending_channels_headS);
  if (x_2244X) {
    goto L17900;}
  else {
    Spending_interruptsS = (16 | (Spending_interruptsS));
    if ((0 == ((Spending_interruptsS) & (Senabled_interruptsS)))) {
      s48_Sstack_limitS = (Sreal_stack_limitS);
      if ((s48_Spending_eventsPS)) {
        s48_Sstack_limitS = (((char *) -1));
        goto L17900;}
      else {
        goto L17900;}}
    else {
      s48_Sstack_limitS = (((char *) -1));
      goto L17900;}}}
 L18107: {
  sig_2245X = *(Sos_signal_ringS + (Sos_signal_ring_startS));
  if ((31 == (Sos_signal_ring_startS))) {
    arg0K0 = 0;
    goto L18111;}
  else {
    arg0K0 = (1 + (Sos_signal_ring_startS));
    goto L18111;}}
 L17958: {
  n_2246X = Senabled_interruptsS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(n_2246X, 2)));
  arg0K0 = 2;
  goto L32828;}
 L14609: {
  count_2247X = arg0K0;
  i_2248X = arg0K1;
  offset_2249X = arg0K2;
  if ((0 == count_2247X)) {
    if ((i_2248X < total_count_1866X)) {
      arg0K0 = i_2248X;
      arg0K1 = offset_2249X;
      goto L11499;}
    else {
      arg0K0 = offset_2249X;
      goto L70985;}}
  else {
    value_2250X = *((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + (1 + offset_2249X)))), 3))));
    addr_2251X = (((char *) (-3 + new_env_1863X))) + (PS_SHIFT_LEFT_INLINE(i_2248X, 3));S48_WRITE_BARRIER(new_env_1863X, addr_2251X, value_2250X);
    *((long *) addr_2251X) = (long) (value_2250X);
    arg0K0 = (-1 + count_2247X);
    arg0K1 = (1 + i_2248X);
    arg0K2 = (1 + offset_2249X);
    goto L14609;}}
 L15404: {
  count_2252X = arg0K0;
  i_2253X = arg0K1;
  offset_2254X = arg0K2;
  if ((0 == count_2252X)) {
    if ((i_2253X < total_count_1877X)) {
      arg0K0 = i_2253X;
      arg0K1 = offset_2254X;
      goto L11849;}
    else {
      arg0K0 = offset_2254X;
      goto L70976;}}
  else {
    value_2255X = *((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + (1 + offset_2254X)))), 8)) + (*((unsigned char *) ((Scode_pointerS) + (2 + offset_2254X))))), 3))));
    addr_2256X = (((char *) (-3 + new_env_1874X))) + (PS_SHIFT_LEFT_INLINE(i_2253X, 3));S48_WRITE_BARRIER(new_env_1874X, addr_2256X, value_2255X);
    *((long *) addr_2256X) = (long) (value_2255X);
    arg0K0 = (-1 + count_2252X);
    arg0K1 = (1 + i_2253X);
    arg0K2 = (2 + offset_2254X);
    goto L15404;}}
 L31426: {
  loc_2257X = arg3K0;
  arg_2258X = arg3K1;
  if ((arg_2258X < top_1278X)) {
    SstackS = ((SstackS) + (0 - (PS_SHIFT_LEFT_INLINE(arg_count_1277X, 3))));
    SvalS = cont_1896X;
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}
  else {
    *((long *) loc_2257X) = (long) ((*((long *) arg_2258X)));
    arg3K0 = (loc_2257X + -8);
    arg3K1 = (arg_2258X + -8);
    goto L31426;}}
 L65913: {

#ifdef USE_DIRECT_THREADING
  pending_interruptP_return_address = &&pending_interruptP_return_5;
#else
  pending_interruptP_return_tag = 5;
#endif
  goto pending_interruptP;
 pending_interruptP_return_5:
  v_2259X = pending_interruptP0_return_value;
  if (v_2259X) {
    arg0K0 = 2;
    goto L33084;}
  else {
    goto L65920;}}
 L65920: {
  v_2260X = s48_call_native_procedure((SvalS), 2);
  arg0K0 = v_2260X;
  goto L65708;}
 L32708: {
  template_2261X = *((long *) (((char *) (-3 + (SvalS)))));
  arg0K0 = (*((long *) (((char *) (-3 + template_2261X)))));
  arg0K1 = skip_1910X;
  arg0K2 = (1 + skip_1910X);
  arg0K3 = template_2261X;
  goto L32468;}
 L66055: {

#ifdef USE_DIRECT_THREADING
  pop_continuationB_return_address = &&pop_continuationB_return_4;
#else
  pop_continuationB_return_tag = 4;
#endif
  goto pop_continuationB;
 pop_continuationB_return_4:
  Scode_pointerS = ((Scode_pointerS) + 2);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L65840: {
  protocol_skip_2262X = arg0K0;
  SstackS = (ScontS);
  cont_2263X = ScontS;
  pointer_2264X = (((char *) (*((long *) cont_2263X)))) + -2;
  size_2265X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) pointer_2264X)), 8)) + (*((unsigned char *) (pointer_2264X + 1)));
  if ((65535 == size_2265X)) {
    arg0K0 = (PS_SHIFT_RIGHT_INLINE((*((long *) (cont_2263X + 8))), 2));
    goto L65851;}
  else {
    arg0K0 = size_2265X;
    goto L65851;}}
 L34158: {
  cont_2266X = arg0K0;
  if ((1 == cont_2266X)) {
    if ((0 == (3 & (SvalS)))) {
      s48_Scallback_return_stack_blockS = 1;
      arg0K0 = (PS_SHIFT_RIGHT_INLINE((SvalS), 2));
      goto L70968;}
    else {
      goto L34173;}}
  else {
    goto L34173;}}
 L66199: {
  v_2267X = arg0K0;
  ScontS = (cont_1935X + (8 + (PS_SHIFT_LEFT_INLINE(v_2267X, 3))));
  merged_arg0K0 = 0;
#ifdef USE_DIRECT_THREADING
  move_args_above_contB_return_address = &&move_args_above_contB_return_9;
#else
  move_args_above_contB_return_tag = 9;
#endif
  goto move_args_above_contB;
 move_args_above_contB_return_9:
  goto L66104;}
 L66104: {
  x_2268X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2268X);
  SvalS = proc_1934X;
  arg0K0 = 1;
  arg0K1 = 25;
  arg0K2 = 0;
  goto L65449;}
 L33313: {
  v_2269X = arg0K0;
  SvalS = v_2269X;
#ifdef USE_DIRECT_THREADING
  pop_continuationB_return_address = &&pop_continuationB_return_5;
#else
  pop_continuationB_return_tag = 5;
#endif
  goto pop_continuationB;
 pop_continuationB_return_5:
  arg0K0 = 1;
  goto L36671;}
 L34241: {
  stack_nargs_2270X = arg0K0;
  list_args_2271X = arg0K1;
  merged_arg0K0 = list_args_2271X;
  merged_arg0K1 = stack_nargs_2270X;
#ifdef USE_DIRECT_THREADING
  pop_args_GlistSAgc_return_address = &&pop_args_GlistSAgc_return_9;
#else
  pop_args_GlistSAgc_return_tag = 9;
#endif
  goto pop_args_GlistSAgc;
 pop_args_GlistSAgc_return_9:
  args_2272X = pop_args_GlistSAgc0_return_value;push_exception_setupB(4, 0);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (args_2272X);
  arg0K0 = 2;
  goto L33796;}
 L36671: {
  bytes_used_2273X = arg0K0;
  Scode_pointerS = ((Scode_pointerS) + (1 + bytes_used_2273X));
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L66384: {
  v_2274X = arg0K0;
  SvalS = v_2274X;
  arg0K0 = 2;
  goto L65840;}
 L33259: {
  if ((1 == (stack_nargs_1947X + list_arg_count_1949X))) {
    if ((1 == stack_nargs_1947X)) {
      v_2275X = *((long *) (SstackS));
      SstackS = ((SstackS) + 8);
      arg0K0 = v_2275X;
      goto L33337;}
    else {
      arg0K0 = (*((long *) (((char *) (-3 + list_args_1948X)))));
      goto L33337;}}
  else {
    arg0K0 = stack_nargs_1947X;
    arg0K1 = list_args_1948X;
    goto L34241;}}
 L33376: {
  v_2276X = arg0K0;
  ScontS = (cont_1958X + (8 + (PS_SHIFT_LEFT_INLINE(v_2276X, 3))));
  merged_arg0K0 = stack_nargs_1947X;
#ifdef USE_DIRECT_THREADING
  move_args_above_contB_return_address = &&move_args_above_contB_return_10;
#else
  move_args_above_contB_return_tag = 10;
#endif
  goto move_args_above_contB;
 move_args_above_contB_return_10:
  arg0K0 = stack_nargs_1947X;
  arg0K1 = list_args_1948X;
  arg0K2 = list_arg_count_1949X;
  goto L65449;}
 L37728: {
  loc_2277X = arg3K0;
  arg_2278X = arg3K1;
  if ((arg_2278X < arg_top_1963X)) {
    SstackS = ((SstackS) + (0 - (PS_SHIFT_LEFT_INLINE(stack_nargs_1947X, 3))));
    if ((count_1961X < stack_nargs_1947X)) {
      merged_arg0K0 = list_args_1948X;
      merged_arg0K1 = (stack_nargs_1947X - count_1961X);
#ifdef USE_DIRECT_THREADING
      pop_args_GlistSAgc_return_address = &&pop_args_GlistSAgc_return_10;
#else
      pop_args_GlistSAgc_return_tag = 10;
#endif
      goto pop_args_GlistSAgc;
     pop_args_GlistSAgc_return_10:
      v_2279X = pop_args_GlistSAgc0_return_value;
      arg0K0 = v_2279X;
      goto L37707;}
    else {
      arg0K0 = stack_nargs_1947X;
      arg0K1 = list_args_1948X;
      goto L37689;}}
  else {
    *((long *) loc_2277X) = (long) ((*((long *) arg_2278X)));
    arg3K0 = (loc_2277X + -8);
    arg3K1 = (arg_2278X + -8);
    goto L37728;}}
 L37580: {
  count_2280X = arg0K0;
  bytes_used_2281X = arg0K1;
  stack_nargs_2282X = arg0K2;
  list_args_2283X = arg0K3;
  list_arg_count_2284X = arg0K4;
  if ((count_2280X == (stack_nargs_2282X + list_arg_count_2284X))) {
    arg_top_2285X = SstackS;
#ifdef USE_DIRECT_THREADING
    pop_continuationB_return_address = &&pop_continuationB_return_6;
#else
    pop_continuationB_return_tag = 6;
#endif
    goto pop_continuationB;
   pop_continuationB_return_6:
    arg3K0 = ((SstackS) + -8);
    arg3K1 = (arg_top_2285X + (-8 + (PS_SHIFT_LEFT_INLINE(stack_nargs_2282X, 3))));
    goto L37612;}
  else {
    merged_arg0K0 = list_args_2283X;
    merged_arg0K1 = stack_nargs_2282X;
#ifdef USE_DIRECT_THREADING
    pop_args_GlistSAgc_return_address = &&pop_args_GlistSAgc_return_11;
#else
    pop_args_GlistSAgc_return_tag = 11;
#endif
    goto pop_args_GlistSAgc;
   pop_args_GlistSAgc_return_11:
    args_2286X = pop_args_GlistSAgc0_return_value;push_exception_setupB(4, 0);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (1);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (args_2286X);
    arg0K0 = 2;
    goto L33796;}}
 L37902: {
push_exception_setupB(5, 8);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (template_1308X);
  arg0K0 = 1;
  goto L33796;}
 L21065: {
  if ((3 == (3 & x_1329X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + x_1329X))))), 2))))) {
      arg0K0 = 5;
      goto L67430;}
    else {
      goto L21071;}}
  else {
    goto L21071;}}
 L56386: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (n_1330X);
  arg0K0 = 1;
  goto L33796;}
 L56381: {
  if ((3 == (3 & n_1330X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + n_1330X))))), 2))))) {
      goto L56386;}
    else {
      goto L56387;}}
  else {
    goto L56387;}}
 L56530: {
  if ((3 == (3 & n_1331X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + n_1331X))))), 2))))) {
      x_2287X = *((double *) (((char *) (-3 + n_1331X))));
      if ((x_2287X == x_2287X)) {
        if ((PS_POS_INF == x_2287X)) {
          arg0K0 = 1;
          goto L56575;}
        else {
          if ((PS_NEG_INF == x_2287X)) {
            arg0K0 = 1;
            goto L56575;}
          else {
            arg0K0 = 5;
            goto L56575;}}}
      else {
        arg0K0 = 1;
        goto L56575;}}
    else {
      goto L56536;}}
  else {
    goto L56536;}}
 L56765: {
  SvalS = 5;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L56748: {
  if ((3 == (3 & n_1971X))) {
    if ((8 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + n_1971X))))), 2))))) {
      goto L56765;}
    else {
      goto L56756;}}
  else {
    goto L56756;}}
 L47953: {
  val_2288X = integer_add(arg2_1335X, y_1336X);
  SvalS = val_2288X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L47970: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1335X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (y_1336X);
  arg0K0 = 2;
  goto L33796;}
 L12472: {
  b_2289X = arg0K0;
  lo_a_2290X = 4294967295 & a_1981X;
  lo_b_2291X = 4294967295 & b_2289X;
  hi_a_2292X = 4294967295 & (PS_SHIFT_RIGHT_INLINE(a_1981X, 32));
  hi_b_2293X = 4294967295 & (PS_SHIFT_RIGHT_INLINE(b_2289X, 32));
  lo_c_2294X = SMALL_MULTIPLY(lo_a_2290X, lo_b_2291X);
  v_2295X = SMALL_MULTIPLY(lo_a_2290X, hi_b_2293X);
  v_2296X = SMALL_MULTIPLY(lo_b_2291X, hi_a_2292X);
  mid_c_2297X = v_2295X + v_2296X;
  c_2298X = lo_c_2294X + (PS_SHIFT_LEFT_INLINE(mid_c_2297X, 32));
  if ((0 < hi_a_2292X)) {
    if ((0 < hi_b_2293X)) {
      val_2299X = integer_multiply(arg2_1338X, y_1339X);
      SvalS = val_2299X;
      Scode_pointerS = ((Scode_pointerS) + 1);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
    else {
      goto L12514;}}
  else {
    goto L12514;}}
 L58522: {
  val_2300X = integer_multiply(arg2_1338X, y_1339X);
  SvalS = val_2300X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L58539: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1338X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (y_1339X);
  arg0K0 = 2;
  goto L33796;}
 L48242: {
  val_2301X = integer_subtract(arg2_1342X, y_1343X);
  SvalS = val_2301X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L48259: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1342X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (y_1343X);
  arg0K0 = 2;
  goto L33796;}
 L12730: {
  b_2302X = arg0K0;
  c_2303X = a_1997X / b_2302X;
  x_2304X = 0 == (a_1997X % b_2302X);
  if (x_2304X) {
    if ((a_1347X < 0)) {
      if ((b_1348X < 0)) {s48_make_availableAgc(24);
        if ((2305843009213693951 < c_2303X)) {
          goto L69100;}
        else {
          if ((c_2303X < -2305843009213693952)) {
            goto L69100;}
          else {
            arg0K0 = (PS_SHIFT_LEFT_INLINE(c_2303X, 2));
            goto L69095;}}}
      else {
        goto L12776;}}
    else {
      if ((b_1348X < 0)) {
        goto L12776;}
      else {s48_make_availableAgc(24);
        if ((2305843009213693951 < c_2303X)) {
          goto L69122;}
        else {
          if ((c_2303X < -2305843009213693952)) {
            goto L69122;}
          else {
            arg0K0 = (PS_SHIFT_LEFT_INLINE(c_2303X, 2));
            goto L69117;}}}}}
  else {push_exception_setupB(5, 1);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (arg2_1345X);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (y_1346X);
    arg0K0 = 2;
    goto L33796;}}
 L58775: {
  div_by_zeroP_2305X = integer_divide(arg2_1345X, y_1346X, &quot_2306X, &rem_2307X, &x_2308X, &y_2309X);
  if (div_by_zeroP_2305X) {
    goto L58805;}
  else {
    if ((0 == (3 & rem_2307X))) {
      if ((0 == rem_2307X)) {
        SvalS = quot_2306X;
        Scode_pointerS = ((Scode_pointerS) + 1);
        arg3K0 = (Scode_pointerS);
        goto L36237;}
      else {
        goto L58805;}}
    else {
      goto L58805;}}}
 L58820: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1345X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (y_1346X);
  arg0K0 = 2;
  goto L33796;}
 L48527: {
  b_2310X = integerE(arg2_1349X, y_1350X);
  if (b_2310X) {
    arg0K0 = 5;
    goto L48531;}
  else {
    arg0K0 = 1;
    goto L48531;}}
 L48547: {
  val_2311X = arg0K0;
  SvalS = val_2311X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L48548: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1349X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (y_1350X);
  arg0K0 = 2;
  goto L33796;}
 L48787: {
  if ((0 == (3 & arg2_1351X))) {
    if ((0 == (3 & y_1352X))) {
      if ((arg2_1351X < y_1352X)) {
        arg0K0 = 5;
        goto L48791;}
      else {
        arg0K0 = 1;
        goto L48791;}}
    else {
      v_2312X = s48_bignum_test((((char *) (-3 + y_1352X))));
      if ((1 == v_2312X)) {
        arg0K0 = 5;
        goto L48791;}
      else {
        arg0K0 = 1;
        goto L48791;}}}
  else {
    if ((0 == (3 & y_1352X))) {
      v_2313X = s48_bignum_test((((char *) (-3 + arg2_1351X))));
      if ((1 == v_2313X)) {
        arg0K0 = 1;
        goto L48791;}
      else {
        arg0K0 = 5;
        goto L48791;}}
    else {
      v_2314X = s48_bignum_compare((((char *) (-3 + arg2_1351X))), (((char *) (-3 + y_1352X))));
      if ((-1 == v_2314X)) {
        arg0K0 = 5;
        goto L48791;}
      else {
        arg0K0 = 1;
        goto L48791;}}}}
 L48807: {
  val_2315X = arg0K0;
  SvalS = val_2315X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L48808: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1351X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (y_1352X);
  arg0K0 = 2;
  goto L33796;}
 L49110: {
  if ((0 == (3 & y_1354X))) {
    if ((0 == (3 & arg2_1353X))) {
      if ((y_1354X < arg2_1353X)) {
        arg0K0 = 5;
        goto L49114;}
      else {
        arg0K0 = 1;
        goto L49114;}}
    else {
      v_2316X = s48_bignum_test((((char *) (-3 + arg2_1353X))));
      if ((1 == v_2316X)) {
        arg0K0 = 5;
        goto L49114;}
      else {
        arg0K0 = 1;
        goto L49114;}}}
  else {
    if ((0 == (3 & arg2_1353X))) {
      v_2317X = s48_bignum_test((((char *) (-3 + y_1354X))));
      if ((1 == v_2317X)) {
        arg0K0 = 1;
        goto L49114;}
      else {
        arg0K0 = 5;
        goto L49114;}}
    else {
      v_2318X = s48_bignum_compare((((char *) (-3 + y_1354X))), (((char *) (-3 + arg2_1353X))));
      if ((-1 == v_2318X)) {
        arg0K0 = 5;
        goto L49114;}
      else {
        arg0K0 = 1;
        goto L49114;}}}}
 L49130: {
  val_2319X = arg0K0;
  SvalS = val_2319X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L49131: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1353X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (y_1354X);
  arg0K0 = 2;
  goto L33796;}
 L49433: {
  b_2320X = integerLE(arg2_1355X, y_1356X);
  if (b_2320X) {
    arg0K0 = 5;
    goto L49437;}
  else {
    arg0K0 = 1;
    goto L49437;}}
 L49453: {
  val_2321X = arg0K0;
  SvalS = val_2321X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L49454: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1355X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (y_1356X);
  arg0K0 = 2;
  goto L33796;}
 L49727: {
  b_2322X = integerGE(arg2_1357X, y_1358X);
  if (b_2322X) {
    arg0K0 = 5;
    goto L49731;}
  else {
    arg0K0 = 1;
    goto L49731;}}
 L49747: {
  val_2323X = arg0K0;
  SvalS = val_2323X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L49748: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1357X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (y_1358X);
  arg0K0 = 2;
  goto L33796;}
 L13145: {
  b_2324X = arg0K0;
  c_2325X = a_2012X / b_2324X;
  if ((a_1362X < 0)) {
    if ((b_1363X < 0)) {
      goto L13191;}
    else {
      goto L13190;}}
  else {
    if ((b_1363X < 0)) {
      goto L13190;}
    else {
      goto L13191;}}}
 L50027: {
  val_2326X = Hinteger_op8731(arg2_1359X, y_1360X);
  SvalS = val_2326X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L50237: {
  b_2327X = arg0K0;
  c_2328X = a_2013X % b_2327X;
  if ((a_1367X < 0)) {
    arg0K0 = (0 - c_2328X);
    goto L50241;}
  else {
    arg0K0 = c_2328X;
    goto L50241;}}
 L50203: {
  val_2329X = Hinteger_op8662(arg2_1364X, y_1365X);
  SvalS = val_2329X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L60125: {
  SvalS = 0;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L60119: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2015X);
  arg0K0 = 1;
  goto L33796;}
 L59106: {
  x_2330X = arg0K0;s48_make_availableAgc(24);
  if ((2305843009213693951 < x_2330X)) {
    goto L59132;}
  else {
    if ((x_2330X < -2305843009213693952)) {
      goto L59132;}
    else {
      arg0K0 = (PS_SHIFT_LEFT_INLINE(x_2330X, 2));
      goto L59127;}}}
 L26713: {
  length_2331X = arg0K0;
  extra_2332X = arg0K1;
  Stemp0S = x_2018X;s48_make_availableAgc((PS_SHIFT_LEFT_INLINE((length_2331X + extra_2332X), 3)));
  value_2333X = Stemp0S;
  Stemp0S = 1;
  if ((0 == (3 & value_2333X))) {
    v_2334X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_2333X, 2)));
    arg3K0 = v_2334X;
    goto L26705;}
  else {
    arg3K0 = (((char *) (-3 + value_2333X)));
    goto L26705;}}
 L50852: {
  x_2335X = arg0K0;
  count_2336X = arg0K1;
  if ((0 == x_2335X)) {
    SvalS = (PS_SHIFT_LEFT_INLINE(count_2336X, 2));
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}
  else {
    arg0K0 = (PS_SHIFT_RIGHT_INLINE(x_2335X, 1));
    arg0K1 = (count_2336X + (1 & x_2335X));
    goto L50852;}}
 L50937: {
  val_2337X = integer_bitwise_and(arg2_1393X, y_1394X);
  SvalS = val_2337X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L51100: {
  val_2338X = integer_bitwise_ior(arg2_1395X, y_1396X);
  SvalS = val_2338X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L51263: {
  val_2339X = integer_bitwise_xor(arg2_1397X, y_1398X);
  SvalS = val_2339X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L59276: {
  v_2340X = (char *) s48_long_to_bignum(x_2029X);
  v_2341X = enter_bignum(v_2340X);
  arg0K0 = v_2341X;
  goto L59271;}
 L59271: {
  val_2342X = arg0K0;
  SvalS = val_2342X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L59298: {
  v_2343X = (char *) s48_long_to_bignum(result_2031X);
  v_2344X = enter_bignum(v_2343X);
  arg0K0 = v_2344X;
  goto L59293;}
 L59293: {
  val_2345X = arg0K0;
  SvalS = val_2345X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L59169: {
  x_2346X = arg0K0;
  y_2347X = arg0K1;
  y_2348X = PS_SHIFT_RIGHT_INLINE(y_2347X, 2);
  merged_arg0K0 = x_2346X;
  merged_arg0K1 = y_2348X;
#ifdef USE_DIRECT_THREADING
  shift_space_return_address = &&shift_space_return_1;
#else
  shift_space_return_tag = 1;
#endif
  goto shift_space;
 shift_space_return_1:
  needed_2349X = shift_space0_return_value;
  Stemp0S = x_2346X;s48_make_availableAgc((PS_SHIFT_LEFT_INLINE(needed_2349X, 3)));
  value_2350X = Stemp0S;
  Stemp0S = 1;
  if ((0 == (3 & value_2350X))) {
    v_2351X = (char *) s48_long_to_bignum((PS_SHIFT_RIGHT_INLINE(value_2350X, 2)));
    arg3K0 = v_2351X;
    goto L59243;}
  else {
    arg3K0 = (((char *) (-3 + value_2350X)));
    goto L59243;}}
 L59320: {
  v_2352X = (char *) s48_long_to_bignum(result_2031X);
  v_2353X = enter_bignum(v_2352X);
  arg0K0 = v_2353X;
  goto L59315;}
 L59315: {
  val_2354X = arg0K0;
  SvalS = val_2354X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L59351: {
  x_2355X = arg3K0;
  external_bignum_2356X = (char *) s48_bignum_arithmetic_shift(x_2355X, y_2033X);
  v_2357X = s48_bignum_fits_in_word_p(external_bignum_2356X, 62, 1);
  if (v_2357X) {
    n_2358X = s48_bignum_to_long(external_bignum_2356X);
    arg0K0 = (PS_SHIFT_LEFT_INLINE(n_2358X, 2));
    goto L59177;}
  else {
    v_2359X = enter_bignum(external_bignum_2356X);
    arg0K0 = v_2359X;
    goto L59177;}}
 L59178: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1399X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (y_1400X);
  arg0K0 = 2;
  goto L33796;}
 L39383: {
  i_2360X = arg0K0;
  rest_list_2361X = arg0K1;
  if ((25 == rest_list_2361X)) {
    SvalS = new_1428X;
    Scode_pointerS = ((Scode_pointerS) + 2);
    arg3K0 = (Scode_pointerS);
    goto L36237;}
  else {
    *((long *) ((((char *) (-3 + new_1428X))) + (PS_SHIFT_LEFT_INLINE(i_2360X, 3)))) = (long) ((*((long *) (((char *) (-3 + rest_list_2361X))))));
    arg0K0 = (1 + i_2360X);
    arg0K1 = (*((long *) ((((char *) (-3 + rest_list_2361X))) + 8)));
    goto L39383;}}
 L39820: {
  i_2362X = arg0K0;
  if ((i_2362X < 0)) {
    SvalS = x_2050X;
    Scode_pointerS = ((Scode_pointerS) + 2);
    arg3K0 = (Scode_pointerS);
    goto L36237;}
  else {
    addr_2363X = (((char *) (-3 + x_2050X))) + (PS_SHIFT_LEFT_INLINE(i_2362X, 3));S48_WRITE_BARRIER(x_2050X, addr_2363X, value_2051X);
    *((long *) addr_2363X) = (long) (value_2051X);
    arg0K0 = (-1 + i_2362X);
    goto L39820;}}
 L51600: {
  i_2364X = arg0K0;
  if ((i_2364X < 0)) {
    SvalS = vector_2055X;
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}
  else {
    *((unsigned char *) ((((char *) (-3 + vector_2055X))) + i_2364X)) = (unsigned char) (init_1463X);
    arg0K0 = (-1 + i_2364X);
    goto L51600;}}
 L51811: {
  i_2365X = arg0K0;
  if ((i_2365X < 0)) {
    SvalS = vector_2059X;
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}
  else {
    *((unsigned char *) ((((char *) (-3 + vector_2059X))) + i_2365X)) = (unsigned char) (init_1477X);
    arg0K0 = (-1 + i_2365X);
    goto L51811;}}
 L52030: {
  i_2366X = arg0K0;
  if ((i_2366X < 0)) {
    SvalS = vector_2060X;
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}
  else {
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = init_1483X;
    goto L52104;}}
 L30766: {
  foo_2367X = arg0K0;
  if ((1 == foo_2367X)) {
    if ((3 == (3 & bucket_2073X))) {
      arg0K0 = (-4 & bucket_2073X);
      goto L30771;}
    else {
      arg0K0 = bucket_2073X;
      goto L30771;}}
  else {
    s2_2368X = *((long *) (((char *) (-3 + foo_2367X))));
    len_2369X = PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + string_1507X))))), 8);
    if ((len_2369X == (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + s2_2368X))))), 8)))) {
      if (((!memcmp((void *)(((char *) (-3 + s2_2368X))), (void *)(((char *) (-3 + string_1507X))),len_2369X)))) {
        arg0K0 = foo_2367X;
        goto L47834;}
      else {
        goto L30786;}}
    else {
      goto L30786;}}}
 L57515: {
  SvalS = 13;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L52220: {
  index_2370X = arg0K0;
  temp_2371X = index_2370X < (Snumber_of_channelsS);
  if (temp_2371X) {
    goto L52335;}
  else {
    x_2372X = add_more_channels(index_2370X);
    if (x_2372X) {
      goto L52335;}
    else {
      arg0K0 = 1;
      arg0K1 = 10;
      goto L52224;}}}
 L52282: {
  v_2373X = ps_open_fd(filename_2081X, 1, &v_2374X);
  arg0K0 = v_2373X;
  arg0K1 = v_2374X;
  goto L52291;}
 L52291: {
  channel_2375X = arg0K0;
  status_2376X = arg0K1;
  if ((status_2376X == NO_ERRORS)) {
    arg0K0 = channel_2375X;
    goto L52220;}
  else {push_exception_setupB(25, 1);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (arg4_1520X);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(mode_1521X, 2)));
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(status_2376X, 2)));
    arg0K0 = 3;
    goto L33796;}}
 L61071: {
  waitP_2377X = arg4K0;
  start_2378X = PS_SHIFT_RIGHT_INLINE(arg3_1528X, 2);
  count_2379X = PS_SHIFT_RIGHT_INLINE(arg2_1527X, 2);
  v_2380X = 4 == (*((long *) (((char *) (-3 + arg5_1530X)))));
  if (v_2380X) {
    if ((3 == (3 & arg4_1529X))) {
      if ((17 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg4_1529X))))), 2))))) {
        if ((3 == (3 & arg4_1529X))) {
          if ((0 == (128 & (*((long *) (((char *) (-11 + arg4_1529X)))))))) {
            if (((PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg4_1529X))))), 8)) < (start_2378X + count_2379X))) {
              goto L52745;}
            else {
              got_2381X = ps_read_fd((PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + arg5_1530X))) + 16))), 2)), ((((char *) (-3 + arg4_1529X))) + start_2378X), count_2379X, waitP_2377X, &eofP_2382X, &pendingP_2383X, &status_2384X);
              if ((status_2384X == NO_ERRORS)) {
                if (eofP_2382X) {
                  if (pendingP_2383X) {
                    addr_2385X = (((char *) (-3 + arg5_1530X))) + 40;S48_WRITE_BARRIER(arg5_1530X, addr_2385X, 5);
                    *((long *) addr_2385X) = (long) (5);
                    arg0K0 = 21;
                    goto L52744;}
                  else {
                    arg0K0 = 21;
                    goto L52744;}}
                else {
                  if (pendingP_2383X) {
                    addr_2386X = (((char *) (-3 + arg5_1530X))) + 40;S48_WRITE_BARRIER(arg5_1530X, addr_2386X, 5);
                    *((long *) addr_2386X) = (long) (5);
                    arg0K0 = 1;
                    goto L52744;}
                  else {
                    arg0K0 = (PS_SHIFT_LEFT_INLINE(got_2381X, 2));
                    goto L52744;}}}
              else {
                addr_2387X = s48_allocate_small(16);
                *((long *) addr_2387X) = (long) (2070);
                x_2388X = 3 + (((long) (addr_2387X + 8)));
                *((long *) (((char *) (-3 + x_2388X)))) = (long) ((PS_SHIFT_LEFT_INLINE(status_2384X, 2)));
                arg0K0 = x_2388X;
                goto L52744;}}}
          else {
            goto L52745;}}
        else {
          goto L52745;}}
      else {
        goto L52745;}}
    else {
      goto L52745;}}
  else {
    goto L52745;}}
 L17669: {
  arg0K0 = (*((long *) ((((char *) (-3 + channel_1553X))) + 40)));
  goto L61423;}
 L17699: {
  val_2389X = *((long *) ((((char *) (-3 + ch_2093X))) + 32));
  addr_2390X = (((char *) (-3 + prev_2094X))) + 32;S48_WRITE_BARRIER(prev_2094X, addr_2390X, val_2389X);
  *((long *) addr_2390X) = (long) (val_2389X);
  addr_2391X = (((char *) (-3 + ch_2093X))) + 32;S48_WRITE_BARRIER(ch_2093X, addr_2391X, 1);
  *((long *) addr_2391X) = (long) (1);
  arg0K0 = (*((long *) ((((char *) (-3 + ch_2093X))) + 40)));
  goto L61423;}
 L24803: {
  v_2392X = arg0K0;
  arg0K0 = (-1 + i_2099X);
  arg0K1 = v_2392X;
  goto L24789;}
 L53304: {
  if ((1 == proposal_1562X)) {
    goto L53316;}
  else {
    addr_2393X = ((char *) (-3 + proposal_1562X));S48_WRITE_BARRIER(proposal_1562X, addr_2393X, 5);
    *((long *) addr_2393X) = (long) (5);
    goto L53316;}}
 L15015: {
  i_2394X = arg0K0;
  stob_2395X = *((long *) ((((char *) (-3 + log_2108X))) + (PS_SHIFT_LEFT_INLINE(i_2394X, 3))));
  if ((1 == stob_2395X)) {
    copies_2396X = *((long *) ((((char *) (-3 + proposal_1563X))) + 24));
    arg0K0 = copies_2396X;
    goto L53667;}
  else {
    value_2397X = *((long *) ((((char *) (-3 + log_2108X))) + (16 + (PS_SHIFT_LEFT_INLINE(i_2394X, 3)))));
    verify_2398X = *((long *) ((((char *) (-3 + log_2108X))) + (24 + (PS_SHIFT_LEFT_INLINE(i_2394X, 3)))));
    if ((29 == verify_2398X)) {
      if ((3 == (3 & stob_2395X))) {
        if ((0 == (128 & (*((long *) (((char *) (-11 + stob_2395X)))))))) {
          goto L15067;}
        else {
          goto L53567;}}
      else {
        goto L53567;}}
    else {
      if ((verify_2398X == (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((((char *) (-3 + stob_2395X))) + (PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + log_2108X))) + (8 + (PS_SHIFT_LEFT_INLINE(i_2394X, 3)))))), 2))))), 2)))) {
        if ((verify_2398X == value_2397X)) {
          goto L15067;}
        else {
          if ((3 == (3 & stob_2395X))) {
            if ((0 == (128 & (*((long *) (((char *) (-11 + stob_2395X)))))))) {
              goto L15067;}
            else {
              goto L53567;}}
          else {
            goto L53567;}}}
      else {
        goto L53567;}}}}
 L14829: {
  arg0K0 = (4 + i_2106X);
  goto L14777;}
 L53567: {
RELEASE_PROPOSAL_LOCK();
  x_2399X = Scurrent_threadS;
  addr_2400X = (((char *) (-3 + x_2399X))) + 24;S48_WRITE_BARRIER(x_2399X, addr_2400X, 1);
  *((long *) addr_2400X) = (long) (1);
  SvalS = 1;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L16469: {
  vector_2401X = arg0K0;
  if ((1 == vector_2401X)) {
    ps_error("Out of space, unable to allocate", 0);
    arg0K0 = vector_2401X;
    goto L16432;}
  else {
    arg0K0 = vector_2401X;
    goto L16432;}}
 L24552: {
  arg0K0 = (4 + i_2120X);
  goto L24530;}
 L24726: {
  arg0K0 = (4 + i_2124X);
  goto L24706;}
 L62778: {
  minutesP_2402X = arg4K0;
#ifdef USE_DIRECT_THREADING
  pending_interruptP_return_address = &&pending_interruptP_return_6;
#else
  pending_interruptP_return_tag = 6;
#endif
  goto pending_interruptP;
 pending_interruptP_return_6:
  x_2403X = pending_interruptP0_return_value;
  if (x_2403X) {
    goto L62808;}
  else {
    if ((0 == (Spending_interruptsS))) {s48_wait_for_event((PS_SHIFT_RIGHT_INLINE(arg2_1655X, 2)), minutesP_2402X);
      goto L62808;}
    else {
      goto L62808;}}}
 L42131: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (proc_2143X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (name_2142X);
  arg0K0 = 2;
  goto L33796;}
 L42432: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (proc_2149X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (name_2148X);
  arg0K0 = 2;
  goto L33796;}
 L61678: {
  val_2404X = arg0K0;
  SvalS = val_2404X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L46055: {
  table_2405X = arg0K0;
  v_2406X = Haction5350(arg2_1669X);
  index_2407X = 1023 & v_2406X;
  link_2408X = *((long *) ((((char *) (-3 + table_2405X))) + (PS_SHIFT_LEFT_INLINE(index_2407X, 3))));
  if ((0 == (3 & link_2408X))) {
    arg0K0 = (3 + (-4 & link_2408X));
    goto L30264;}
  else {
    arg0K0 = link_2408X;
    goto L30264;}}
 L65358: {
  x_2409X = arg0K0;
  SvalS = (PS_SHIFT_LEFT_INLINE(x_2409X, 2));
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L68179: {
  SvalS = 13;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L54134: {
  l_2410X = arg0K0;
  i_2411X = arg0K1;
  if ((i_2411X < 0)) {
    SvalS = obj_2170X;
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}
  else {
    d_2412X = *((long *) (((char *) (-3 + l_2410X))));
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = (PS_SHIFT_RIGHT_INLINE(d_2412X, 8));
    goto L54205;}}
 L42506: {
push_exception_setupB(8, 2);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1722X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg2_1721X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(index_1723X, 2)));
  arg0K0 = 3;
  goto L33796;}
 L42496: {
  arg0K0 = (*((long *) ((((char *) (-3 + arg3_1722X))) + (PS_SHIFT_LEFT_INLINE(index_1723X, 3)))));
  goto L42505;}
 L42505: {
  value_2413X = arg0K0;
  SvalS = value_2413X;
  Scode_pointerS = ((Scode_pointerS) + 2);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L42794: {
push_exception_setupB(8, 2);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg4_1729X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1728X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(index_1730X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (value_1731X);
  arg0K0 = 4;
  goto L33796;}
 L42784: {
  addr_2414X = (((char *) (-3 + arg4_1729X))) + (PS_SHIFT_LEFT_INLINE(index_1730X, 3));S48_WRITE_BARRIER(arg4_1729X, addr_2414X, value_1731X);
  *((long *) addr_2414X) = (long) (value_1731X);
  goto L42793;}
 L42793: {
  SvalS = 13;
  Scode_pointerS = ((Scode_pointerS) + 2);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L42749: {
push_exception_setupB(6, 2);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg4_1729X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg3_1728X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(index_1730X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (value_1731X);
  arg0K0 = 4;
  goto L33796;}
 L34483: {
  x_2415X = arg0K0;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2415X);
  if (okP_2184X) {
    arg0K0 = (PS_SHIFT_LEFT_INLINE(count_2186X, 2));
    goto L34493;}
  else {
    arg0K0 = 1;
    goto L34493;}}
 L34846: {
  x_2416X = arg0K0;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2416X);
  if (okP_2190X) {
    arg0K0 = (PS_SHIFT_LEFT_INLINE(count_2193X, 2));
    goto L34856;}
  else {
    arg0K0 = 1;
    goto L34856;}}
 L43155: {
push_exception_setupB(5, 2);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (port_2196X);
  arg0K0 = 1;
  goto L33796;}
 L43357: {
push_exception_setupB(5, 2);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (port_2203X);
  arg0K0 = 1;
  goto L33796;}
 L43572: {
push_exception_setupB(5, 2);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (byte_2208X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (port_2209X);
  arg0K0 = 2;
  goto L33796;}
 L43937: {
push_exception_setupB(5, 2);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (port_2215X);
  arg0K0 = 1;
  goto L33796;}
 L43793: {
  i_2417X = arg0K0;
  p_2418X = *((long *) ((((char *) (-3 + port_2215X))) + 64));
  codec_2419X = *((long *) ((((char *) (-3 + port_2215X))) + 8));
  l_2420X = PS_SHIFT_RIGHT_INLINE(p_2418X, 2);
  if ((i_2417X == l_2420X)) {
    val_2421X = PS_SHIFT_LEFT_INLINE(i_2417X, 2);
    addr_2422X = (((char *) (-3 + port_2215X))) + 56;S48_WRITE_BARRIER(port_2215X, addr_2422X, val_2421X);
    *((long *) addr_2422X) = (long) (val_2421X);push_exception_setupB(14, 2);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (port_2215X);
    arg0K0 = 1;
    goto L33796;}
  else {
    if ((0 == (3 & codec_2419X))) {
      encoding_2423X = PS_SHIFT_RIGHT_INLINE(codec_2419X, 2);
      buffer_2424X = (((char *) (-3 + b_2216X))) + i_2417X;
      count_2425X = l_2420X - i_2417X;
      if ((0 == encoding_2423X)) {
        arg4K0 = 1;
        arg4K1 = 1;
        arg4K2 = 0;
        arg0K3 = (*((unsigned char *) buffer_2424X));
        arg0K4 = 1;
        goto L43838;}
      else {
        if ((1 == encoding_2423X)) {
          arg4K0 = 1;
          arg4K1 = 1;
          arg4K2 = 0;
          arg0K3 = (*((unsigned char *) buffer_2424X));
          arg0K4 = 1;
          goto L43838;}
        else {
          if ((2 == encoding_2423X)) {
            okP_2426X = decode_scalar_valueUutf_8(buffer_2424X, count_2425X, &incompleteP_2427X, &value_2428X, &count_2429X);
            arg4K0 = 1;
            arg4K1 = okP_2426X;
            arg4K2 = incompleteP_2427X;
            arg0K3 = value_2428X;
            arg0K4 = count_2429X;
            goto L43838;}
          else {
            if ((3 == encoding_2423X)) {
              okP_2430X = decode_scalar_valueUutf_16le(buffer_2424X, count_2425X, &incompleteP_2431X, &value_2432X, &count_2433X);
              arg4K0 = 1;
              arg4K1 = okP_2430X;
              arg4K2 = incompleteP_2431X;
              arg0K3 = value_2432X;
              arg0K4 = count_2433X;
              goto L43838;}
            else {
              if ((4 == encoding_2423X)) {
                okP_2434X = decode_scalar_valueUutf_16be(buffer_2424X, count_2425X, &incompleteP_2435X, &value_2436X, &count_2437X);
                arg4K0 = 1;
                arg4K1 = okP_2434X;
                arg4K2 = incompleteP_2435X;
                arg0K3 = value_2436X;
                arg0K4 = count_2437X;
                goto L43838;}
              else {
                if ((5 == encoding_2423X)) {
                  if ((count_2425X < 4)) {
                    arg4K0 = 1;
                    arg4K1 = 1;
                    arg4K2 = 1;
                    arg0K3 = 0;
                    arg0K4 = 4;
                    goto L43838;}
                  else {
                    code_point_2438X = (((*((unsigned char *) buffer_2424X)) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_2424X + 1))), 8))) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_2424X + 2))), 16))) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_2424X + 3))), 24));
                    if ((code_point_2438X < 0)) {
                      arg4K0 = 1;
                      arg4K1 = 0;
                      arg4K2 = 0;
                      arg0K3 = 0;
                      arg0K4 = 0;
                      goto L43838;}
                    else {
                      if ((55295 < code_point_2438X)) {
                        if ((code_point_2438X < 57344)) {
                          arg4K0 = 1;
                          arg4K1 = 0;
                          arg4K2 = 0;
                          arg0K3 = 0;
                          arg0K4 = 0;
                          goto L43838;}
                        else {
                          if ((1114111 < code_point_2438X)) {
                            arg4K0 = 1;
                            arg4K1 = 0;
                            arg4K2 = 0;
                            arg0K3 = 0;
                            arg0K4 = 0;
                            goto L43838;}
                          else {
                            arg4K0 = 1;
                            arg4K1 = 1;
                            arg4K2 = 0;
                            arg0K3 = code_point_2438X;
                            arg0K4 = 4;
                            goto L43838;}}}
                      else {
                        arg4K0 = 1;
                        arg4K1 = 1;
                        arg4K2 = 0;
                        arg0K3 = code_point_2438X;
                        arg0K4 = 4;
                        goto L43838;}}}}
                else {
                  if ((6 == encoding_2423X)) {
                    if ((count_2425X < 4)) {
                      arg4K0 = 1;
                      arg4K1 = 1;
                      arg4K2 = 1;
                      arg0K3 = 0;
                      arg0K4 = 4;
                      goto L43838;}
                    else {
                      code_point_2439X = (((PS_SHIFT_LEFT_INLINE((*((unsigned char *) buffer_2424X)), 24)) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_2424X + 1))), 16))) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_2424X + 2))), 8))) + (*((unsigned char *) (buffer_2424X + 3)));
                      if ((code_point_2439X < 0)) {
                        arg4K0 = 1;
                        arg4K1 = 0;
                        arg4K2 = 0;
                        arg0K3 = 0;
                        arg0K4 = 0;
                        goto L43838;}
                      else {
                        if ((55295 < code_point_2439X)) {
                          if ((code_point_2439X < 57344)) {
                            arg4K0 = 1;
                            arg4K1 = 0;
                            arg4K2 = 0;
                            arg0K3 = 0;
                            arg0K4 = 0;
                            goto L43838;}
                          else {
                            if ((1114111 < code_point_2439X)) {
                              arg4K0 = 1;
                              arg4K1 = 0;
                              arg4K2 = 0;
                              arg0K3 = 0;
                              arg0K4 = 0;
                              goto L43838;}
                            else {
                              arg4K0 = 1;
                              arg4K1 = 1;
                              arg4K2 = 0;
                              arg0K3 = code_point_2439X;
                              arg0K4 = 4;
                              goto L43838;}}}
                        else {
                          arg4K0 = 1;
                          arg4K1 = 1;
                          arg4K2 = 0;
                          arg0K3 = code_point_2439X;
                          arg0K4 = 4;
                          goto L43838;}}}}
                  else {
                    arg4K0 = 0;
                    arg4K1 = 0;
                    arg4K2 = 0;
                    arg0K3 = 0;
                    arg0K4 = 0;
                    goto L43838;}}}}}}}}
    else {
      val_2440X = PS_SHIFT_LEFT_INLINE(i_2417X, 2);
      addr_2441X = (((char *) (-3 + port_2215X))) + 56;S48_WRITE_BARRIER(port_2215X, addr_2441X, val_2440X);
      *((long *) addr_2441X) = (long) (val_2440X);push_exception_setupB(14, 2);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (port_2215X);
      arg0K0 = 1;
      goto L33796;}}}
 L44585: {
push_exception_setupB(5, 2);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (port_2217X);
  arg0K0 = 1;
  goto L33796;}
 L44441: {
  i_2442X = arg0K0;
  p_2443X = *((long *) ((((char *) (-3 + port_2217X))) + 64));
  codec_2444X = *((long *) ((((char *) (-3 + port_2217X))) + 8));
  l_2445X = PS_SHIFT_RIGHT_INLINE(p_2443X, 2);
  if ((i_2442X == l_2445X)) {push_exception_setupB(14, 2);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (port_2217X);
    arg0K0 = 1;
    goto L33796;}
  else {
    if ((0 == (3 & codec_2444X))) {
      encoding_2446X = PS_SHIFT_RIGHT_INLINE(codec_2444X, 2);
      buffer_2447X = (((char *) (-3 + b_2218X))) + i_2442X;
      count_2448X = l_2445X - i_2442X;
      if ((0 == encoding_2446X)) {
        arg4K0 = 1;
        arg4K1 = 1;
        arg4K2 = 0;
        arg0K3 = (*((unsigned char *) buffer_2447X));
        arg0K4 = 1;
        goto L44486;}
      else {
        if ((1 == encoding_2446X)) {
          arg4K0 = 1;
          arg4K1 = 1;
          arg4K2 = 0;
          arg0K3 = (*((unsigned char *) buffer_2447X));
          arg0K4 = 1;
          goto L44486;}
        else {
          if ((2 == encoding_2446X)) {
            okP_2449X = decode_scalar_valueUutf_8(buffer_2447X, count_2448X, &incompleteP_2450X, &value_2451X, &count_2452X);
            arg4K0 = 1;
            arg4K1 = okP_2449X;
            arg4K2 = incompleteP_2450X;
            arg0K3 = value_2451X;
            arg0K4 = count_2452X;
            goto L44486;}
          else {
            if ((3 == encoding_2446X)) {
              okP_2453X = decode_scalar_valueUutf_16le(buffer_2447X, count_2448X, &incompleteP_2454X, &value_2455X, &count_2456X);
              arg4K0 = 1;
              arg4K1 = okP_2453X;
              arg4K2 = incompleteP_2454X;
              arg0K3 = value_2455X;
              arg0K4 = count_2456X;
              goto L44486;}
            else {
              if ((4 == encoding_2446X)) {
                okP_2457X = decode_scalar_valueUutf_16be(buffer_2447X, count_2448X, &incompleteP_2458X, &value_2459X, &count_2460X);
                arg4K0 = 1;
                arg4K1 = okP_2457X;
                arg4K2 = incompleteP_2458X;
                arg0K3 = value_2459X;
                arg0K4 = count_2460X;
                goto L44486;}
              else {
                if ((5 == encoding_2446X)) {
                  if ((count_2448X < 4)) {
                    arg4K0 = 1;
                    arg4K1 = 1;
                    arg4K2 = 1;
                    arg0K3 = 0;
                    arg0K4 = 4;
                    goto L44486;}
                  else {
                    code_point_2461X = (((*((unsigned char *) buffer_2447X)) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_2447X + 1))), 8))) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_2447X + 2))), 16))) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_2447X + 3))), 24));
                    if ((code_point_2461X < 0)) {
                      arg4K0 = 1;
                      arg4K1 = 0;
                      arg4K2 = 0;
                      arg0K3 = 0;
                      arg0K4 = 0;
                      goto L44486;}
                    else {
                      if ((55295 < code_point_2461X)) {
                        if ((code_point_2461X < 57344)) {
                          arg4K0 = 1;
                          arg4K1 = 0;
                          arg4K2 = 0;
                          arg0K3 = 0;
                          arg0K4 = 0;
                          goto L44486;}
                        else {
                          if ((1114111 < code_point_2461X)) {
                            arg4K0 = 1;
                            arg4K1 = 0;
                            arg4K2 = 0;
                            arg0K3 = 0;
                            arg0K4 = 0;
                            goto L44486;}
                          else {
                            arg4K0 = 1;
                            arg4K1 = 1;
                            arg4K2 = 0;
                            arg0K3 = code_point_2461X;
                            arg0K4 = 4;
                            goto L44486;}}}
                      else {
                        arg4K0 = 1;
                        arg4K1 = 1;
                        arg4K2 = 0;
                        arg0K3 = code_point_2461X;
                        arg0K4 = 4;
                        goto L44486;}}}}
                else {
                  if ((6 == encoding_2446X)) {
                    if ((count_2448X < 4)) {
                      arg4K0 = 1;
                      arg4K1 = 1;
                      arg4K2 = 1;
                      arg0K3 = 0;
                      arg0K4 = 4;
                      goto L44486;}
                    else {
                      code_point_2462X = (((PS_SHIFT_LEFT_INLINE((*((unsigned char *) buffer_2447X)), 24)) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_2447X + 1))), 16))) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) (buffer_2447X + 2))), 8))) + (*((unsigned char *) (buffer_2447X + 3)));
                      if ((code_point_2462X < 0)) {
                        arg4K0 = 1;
                        arg4K1 = 0;
                        arg4K2 = 0;
                        arg0K3 = 0;
                        arg0K4 = 0;
                        goto L44486;}
                      else {
                        if ((55295 < code_point_2462X)) {
                          if ((code_point_2462X < 57344)) {
                            arg4K0 = 1;
                            arg4K1 = 0;
                            arg4K2 = 0;
                            arg0K3 = 0;
                            arg0K4 = 0;
                            goto L44486;}
                          else {
                            if ((1114111 < code_point_2462X)) {
                              arg4K0 = 1;
                              arg4K1 = 0;
                              arg4K2 = 0;
                              arg0K3 = 0;
                              arg0K4 = 0;
                              goto L44486;}
                            else {
                              arg4K0 = 1;
                              arg4K1 = 1;
                              arg4K2 = 0;
                              arg0K3 = code_point_2462X;
                              arg0K4 = 4;
                              goto L44486;}}}
                        else {
                          arg4K0 = 1;
                          arg4K1 = 1;
                          arg4K2 = 0;
                          arg0K3 = code_point_2462X;
                          arg0K4 = 4;
                          goto L44486;}}}}
                  else {
                    arg4K0 = 0;
                    arg4K1 = 0;
                    arg4K2 = 0;
                    arg0K3 = 0;
                    arg0K4 = 0;
                    goto L44486;}}}}}}}}
    else {push_exception_setupB(14, 2);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (port_2217X);
      arg0K0 = 1;
      goto L33796;}}}
 L45200: {
push_exception_setupB(5, 2);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (Kchar_2219X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (port_2220X);
  arg0K0 = 2;
  goto L33796;}
 L45146: {
  encoding_2463X = PS_SHIFT_RIGHT_INLINE(codec_2221X, 2);
  value_2464X = PS_SHIFT_RIGHT_INLINE(Kchar_2219X, 8);
  buffer_2465X = (((char *) (-3 + b_2222X))) + i_2223X;
  count_2466X = l_2224X - i_2223X;
  if ((0 == encoding_2463X)) {
    if ((count_2466X < 1)) {
      arg4K0 = 1;
      arg4K1 = 1;
      arg4K2 = 1;
      arg0K3 = 1;
      goto L45158;}
    else {
      if ((value_2464X < 128)) {
        *((unsigned char *) buffer_2465X) = (unsigned char) (value_2464X);
        arg4K0 = 1;
        arg4K1 = 1;
        arg4K2 = 0;
        arg0K3 = 1;
        goto L45158;}
      else {
        arg4K0 = 1;
        arg4K1 = 0;
        arg4K2 = 0;
        arg0K3 = 0;
        goto L45158;}}}
  else {
    if ((1 == encoding_2463X)) {
      if ((count_2466X < 1)) {
        arg4K0 = 1;
        arg4K1 = 1;
        arg4K2 = 1;
        arg0K3 = 1;
        goto L45158;}
      else {
        if ((value_2464X < 256)) {
          *((unsigned char *) buffer_2465X) = (unsigned char) (value_2464X);
          arg4K0 = 1;
          arg4K1 = 1;
          arg4K2 = 0;
          arg0K3 = 1;
          goto L45158;}
        else {
          arg4K0 = 1;
          arg4K1 = 0;
          arg4K2 = 0;
          arg0K3 = 0;
          goto L45158;}}}
    else {
      if ((2 == encoding_2463X)) {
        encoding_okP_2467X = encode_scalar_valueUutf_8(value_2464X, buffer_2465X, count_2466X, &out_of_spaceP_2468X, &count_2469X);
        arg4K0 = 1;
        arg4K1 = encoding_okP_2467X;
        arg4K2 = out_of_spaceP_2468X;
        arg0K3 = count_2469X;
        goto L45158;}
      else {
        if ((3 == encoding_2463X)) {
          encoding_okP_2470X = encode_scalar_valueUutf_16le(value_2464X, buffer_2465X, count_2466X, &out_of_spaceP_2471X, &count_2472X);
          arg4K0 = 1;
          arg4K1 = encoding_okP_2470X;
          arg4K2 = out_of_spaceP_2471X;
          arg0K3 = count_2472X;
          goto L45158;}
        else {
          if ((4 == encoding_2463X)) {
            encoding_okP_2473X = encode_scalar_valueUutf_16be(value_2464X, buffer_2465X, count_2466X, &out_of_spaceP_2474X, &count_2475X);
            arg4K0 = 1;
            arg4K1 = encoding_okP_2473X;
            arg4K2 = out_of_spaceP_2474X;
            arg0K3 = count_2475X;
            goto L45158;}
          else {
            if ((5 == encoding_2463X)) {
              if ((count_2466X < 4)) {
                arg4K0 = 1;
                arg4K1 = 1;
                arg4K2 = 1;
                arg0K3 = 4;
                goto L45158;}
              else {
                *((unsigned char *) buffer_2465X) = (unsigned char) ((255 & value_2464X));
                *((unsigned char *) (buffer_2465X + 1)) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE((65280 & value_2464X), 8)));
                *((unsigned char *) (buffer_2465X + 2)) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE((16711680 & value_2464X), 16)));
                *((unsigned char *) (buffer_2465X + 3)) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE(value_2464X, 24)));
                arg4K0 = 1;
                arg4K1 = 1;
                arg4K2 = 0;
                arg0K3 = 4;
                goto L45158;}}
            else {
              if ((6 == encoding_2463X)) {
                if ((count_2466X < 4)) {
                  arg4K0 = 1;
                  arg4K1 = 1;
                  arg4K2 = 1;
                  arg0K3 = 4;
                  goto L45158;}
                else {
                  *((unsigned char *) buffer_2465X) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE(value_2464X, 24)));
                  *((unsigned char *) (buffer_2465X + 1)) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE((16711680 & value_2464X), 16)));
                  *((unsigned char *) (buffer_2465X + 2)) = (unsigned char) ((PS_SHIFT_RIGHT_LOGICAL_INLINE((65280 & value_2464X), 8)));
                  *((unsigned char *) (buffer_2465X + 3)) = (unsigned char) ((255 & value_2464X));
                  arg4K0 = 1;
                  arg4K1 = 1;
                  arg4K2 = 0;
                  arg0K3 = 4;
                  goto L45158;}}
              else {
                arg4K0 = 0;
                arg4K1 = 0;
                arg4K2 = 0;
                arg0K3 = 0;
                goto L45158;}}}}}}}}
 L45081: {
  codec_okP_2476X = arg4K0;
  encoding_okP_2477X = arg4K1;
  out_of_spaceP_2478X = arg4K2;
  count_2479X = arg0K3;
  if (codec_okP_2476X) {
    if (encoding_okP_2477X) {
      if (out_of_spaceP_2478X) {push_exception_setupB(14, 2);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (Kchar_2219X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (port_2220X);
        arg0K0 = 2;
        goto L33796;}
      else {
        i_2480X = i_2223X + count_2479X;
        if ((i_2480X == l_2224X)) {push_exception_setupB(14, 2);
          SstackS = ((SstackS) + -8);
          *((long *) (SstackS)) = (long) (Kchar_2219X);
          SstackS = ((SstackS) + -8);
          *((long *) (SstackS)) = (long) (port_2220X);
          arg0K0 = 2;
          goto L33796;}
        else {
          encoding_2481X = PS_SHIFT_RIGHT_INLINE(codec_2221X, 2);
          buffer_2482X = (((char *) (-3 + b_2222X))) + i_2480X;
          count_2483X = l_2224X - i_2480X;
          if ((0 == encoding_2481X)) {
            if ((count_2483X < 1)) {
              arg4K0 = 1;
              arg4K1 = 1;
              arg0K2 = 1;
              goto L45123;}
            else {
              *((unsigned char *) buffer_2482X) = (unsigned char) (10);
              arg4K0 = 1;
              arg4K1 = 0;
              arg0K2 = 1;
              goto L45123;}}
          else {
            if ((1 == encoding_2481X)) {
              if ((count_2483X < 1)) {
                arg4K0 = 1;
                arg4K1 = 1;
                arg0K2 = 1;
                goto L45123;}
              else {
                *((unsigned char *) buffer_2482X) = (unsigned char) (10);
                arg4K0 = 1;
                arg4K1 = 0;
                arg0K2 = 1;
                goto L45123;}}
            else {
              if ((2 == encoding_2481X)) {
                encoding_okP_2484X = encode_scalar_valueUutf_8(10, buffer_2482X, count_2483X, &out_of_spaceP_2485X, &count_2486X);
                arg4K0 = encoding_okP_2484X;
                arg4K1 = out_of_spaceP_2485X;
                arg0K2 = count_2486X;
                goto L45123;}
              else {
                if ((3 == encoding_2481X)) {
                  encoding_okP_2487X = encode_scalar_valueUutf_16le(10, buffer_2482X, count_2483X, &out_of_spaceP_2488X, &count_2489X);
                  arg4K0 = encoding_okP_2487X;
                  arg4K1 = out_of_spaceP_2488X;
                  arg0K2 = count_2489X;
                  goto L45123;}
                else {
                  if ((4 == encoding_2481X)) {
                    encoding_okP_2490X = encode_scalar_valueUutf_16be(10, buffer_2482X, count_2483X, &out_of_spaceP_2491X, &count_2492X);
                    arg4K0 = encoding_okP_2490X;
                    arg4K1 = out_of_spaceP_2491X;
                    arg0K2 = count_2492X;
                    goto L45123;}
                  else {
                    if ((5 == encoding_2481X)) {
                      if ((count_2483X < 4)) {
                        arg4K0 = 1;
                        arg4K1 = 1;
                        arg0K2 = 4;
                        goto L45123;}
                      else {
                        *((unsigned char *) buffer_2482X) = (unsigned char) (10);
                        *((unsigned char *) (buffer_2482X + 1)) = (unsigned char) (0);
                        *((unsigned char *) (buffer_2482X + 2)) = (unsigned char) (0);
                        *((unsigned char *) (buffer_2482X + 3)) = (unsigned char) (167772160);
                        arg4K0 = 1;
                        arg4K1 = 0;
                        arg0K2 = 4;
                        goto L45123;}}
                    else {
                      if ((6 == encoding_2481X)) {
                        if ((count_2483X < 4)) {
                          arg4K0 = 1;
                          arg4K1 = 1;
                          arg0K2 = 4;
                          goto L45123;}
                        else {
                          *((unsigned char *) buffer_2482X) = (unsigned char) (167772160);
                          *((unsigned char *) (buffer_2482X + 1)) = (unsigned char) (0);
                          *((unsigned char *) (buffer_2482X + 2)) = (unsigned char) (0);
                          *((unsigned char *) (buffer_2482X + 3)) = (unsigned char) (10);
                          arg4K0 = 1;
                          arg4K1 = 0;
                          arg0K2 = 4;
                          goto L45123;}}
                      else {
                        arg4K0 = 0;
                        arg4K1 = 0;
                        arg0K2 = 0;
                        goto L45123;}}}}}}}}}}
    else {push_exception_setupB(14, 2);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (Kchar_2219X);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (port_2220X);
      arg0K0 = 2;
      goto L33796;}}
  else {push_exception_setupB(5, 2);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (Kchar_2219X);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (port_2220X);
    arg0K0 = 2;
    goto L33796;}}
 L55265: {
  i_2493X = arg0K0;
  if ((i_2493X < len_1822X)) {
    *((unsigned char *) ((((char *) (-3 + vector_2238X))) + i_2493X)) = (unsigned char) ((((unsigned char) (*(raw_1821X + i_2493X)))));
    arg0K0 = (1 + i_2493X);
    goto L55265;}
  else {
    SvalS = vector_2238X;
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}}
 L57369: {
  { long ignoreXX;
  PS_WRITE_CHAR(10, out_1826X, ignoreXX) }
  SvalS = 13;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L32842: {
  SvalS = (*((long *) ((((char *) (-3 + handlers_1829X))) + (PS_SHIFT_LEFT_INLINE(i_1827X, 3)))));
  obj_2494X = SvalS;
  if ((3 == (3 & obj_2494X))) {
    if ((3 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_2494X))))), 2))))) {
      goto L32859;}
    else {
      goto L32898;}}
  else {
    goto L32898;}}
 L32884: {
  ps_error("interrupt handler is not a vector", 0);
  goto L32842;}
 L17880: {
  x_2495X = arg0K0;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2495X);
  arg0K0 = 3;
  goto L32828;}
 L17900: {
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (channel_2243X);
  x_2496X = *((long *) ((((char *) (-3 + channel_2243X))) + 48));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2496X);
  x_2497X = *((long *) ((((char *) (-3 + channel_2243X))) + 40));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2497X);
  n_2498X = Senabled_interruptsS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(n_2498X, 2)));
  arg0K0 = 4;
  goto L32828;}
 L18111: {
  v_2499X = arg0K0;
  Sos_signal_ring_startS = v_2499X;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(sig_2245X, 2)));
  if (((Sos_signal_ring_readyS) == (Sos_signal_ring_startS))) {
    goto L17932;}
  else {
    Spending_interruptsS = (32 | (Spending_interruptsS));
    if ((0 == ((Spending_interruptsS) & (Senabled_interruptsS)))) {
      s48_Sstack_limitS = (Sreal_stack_limitS);
      if ((s48_Spending_eventsPS)) {
        s48_Sstack_limitS = (((char *) -1));
        goto L17932;}
      else {
        goto L17932;}}
    else {
      s48_Sstack_limitS = (((char *) -1));
      goto L17932;}}}
 L11499: {
  i_2500X = arg0K0;
  offset_2501X = arg0K1;
  if ((i_2500X == total_count_1866X)) {
    arg0K0 = offset_2501X;
    goto L70985;}
  else {
    env_2502X = *((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + (1 + offset_2501X)))), 3))));
    count_2503X = *((unsigned char *) ((Scode_pointerS) + (2 + offset_2501X)));
    arg0K0 = count_2503X;
    arg0K1 = i_2500X;
    arg0K2 = (2 + offset_2501X);
    goto L11516;}}
 L70985: {
  bytes_used_2504X = arg0K0;
  SvalS = new_env_1248X;
  Scode_pointerS = ((Scode_pointerS) + (1 + bytes_used_2504X));
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L11849: {
  i_2505X = arg0K0;
  offset_2506X = arg0K1;
  if ((i_2505X == total_count_1877X)) {
    arg0K0 = offset_2506X;
    goto L70976;}
  else {
    env_2507X = *((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + (1 + offset_2506X)))), 8)) + (*((unsigned char *) ((Scode_pointerS) + (2 + offset_2506X))))), 3))));
    index_2508X = 2 + offset_2506X;
    count_2509X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + (1 + index_2508X)))), 8)) + (*((unsigned char *) ((Scode_pointerS) + (2 + index_2508X))));
    arg0K0 = count_2509X;
    arg0K1 = i_2505X;
    arg0K2 = (4 + offset_2506X);
    goto L11866;}}
 L70976: {
  bytes_used_2510X = arg0K0;
  SvalS = new_env_1254X;
  Scode_pointerS = ((Scode_pointerS) + (1 + bytes_used_2510X));
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L65851: {
  v_2511X = arg0K0;
  ScontS = (cont_2263X + (8 + (PS_SHIFT_LEFT_INLINE(v_2511X, 3))));
  v_2512X = *((long *) (SstackS));
  SstackS = ((SstackS) + 8);
  v_2513X = s48_invoke_native_continuation((((long) (((char *) v_2512X)))), protocol_skip_2262X);
  arg0K0 = v_2513X;
  goto L65708;}
 L34173: {
  SstackS = (Sbottom_of_stackS);
  Sheap_continuationS = 1;
  ScontS = (Sbottom_of_stackS);push_exception_setupB(5, 0);
  x_2514X = SvalS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2514X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (cont_2266X);
  arg0K0 = 2;
  goto L33796;}
 L33337: {
  v_2515X = arg0K0;
  SvalS = v_2515X;
  arg0K0 = cont_1956X;
  goto L34158;}
 L37707: {
  x_2516X = arg0K0;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2516X);
  Scode_pointerS = ((Scode_pointerS) + 4);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L37689: {
  stack_nargs_2517X = arg0K0;
  l_2518X = arg0K1;
  if ((count_1961X == stack_nargs_2517X)) {
    arg0K0 = l_2518X;
    goto L37707;}
  else {
    x_2519X = *((long *) (((char *) (-3 + l_2518X))));
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (x_2519X);
    arg0K0 = (1 + stack_nargs_2517X);
    arg0K1 = (*((long *) ((((char *) (-3 + l_2518X))) + 8)));
    goto L37689;}}
 L37612: {
  loc_2520X = arg3K0;
  arg_2521X = arg3K1;
  if ((arg_2521X < arg_top_2285X)) {
    SstackS = ((SstackS) + (0 - (PS_SHIFT_LEFT_INLINE(stack_nargs_2282X, 3))));
    if ((0 == list_arg_count_2284X)) {
      goto L37599;}
    else {
      merged_arg0K0 = list_args_2283X;
      merged_arg0K1 = list_arg_count_2284X;
#ifdef USE_DIRECT_THREADING
      push_list_return_address = &&push_list_return_3;
#else
      push_list_return_tag = 3;
#endif
      goto push_list;
     push_list_return_3:
      goto L37599;}}
  else {
    *((long *) loc_2520X) = (long) ((*((long *) arg_2521X)));
    arg3K0 = (loc_2520X + -8);
    arg3K1 = (arg_2521X + -8);
    goto L37612;}}
 L21071: {
  if ((3 == (3 & x_1329X))) {
    if ((11 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + x_1329X))))), 2))))) {
      arg0K0 = 5;
      goto L67430;}
    else {
      arg0K0 = 1;
      goto L67430;}}
  else {
    arg0K0 = 1;
    goto L67430;}}
 L56387: {
  SvalS = 1;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L56575: {
  val_2522X = arg0K0;
  SvalS = val_2522X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L56536: {
  if ((3 == (3 & n_1331X))) {
    if ((11 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + n_1331X))))), 2))))) {push_exception_setupB(5, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (n_1331X);
      arg0K0 = 1;
      goto L33796;}
    else {
      goto L56540;}}
  else {
    goto L56540;}}
 L56756: {
  if ((3 == (3 & n_1971X))) {
    if ((18 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + n_1971X))))), 2))))) {
      goto L56765;}
    else {
      goto L56766;}}
  else {
    goto L56766;}}
 L12514: {
  if ((2305843009213693951 < lo_c_2294X)) {
    val_2523X = integer_multiply(arg2_1338X, y_1339X);
    SvalS = val_2523X;
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}
  else {
    if ((lo_c_2294X < 0)) {
      val_2524X = integer_multiply(arg2_1338X, y_1339X);
      SvalS = val_2524X;
      Scode_pointerS = ((Scode_pointerS) + 1);
      arg3K0 = (Scode_pointerS);
      goto L36237;}
    else {
      if ((536870912 < mid_c_2297X)) {
        val_2525X = integer_multiply(arg2_1338X, y_1339X);
        SvalS = val_2525X;
        Scode_pointerS = ((Scode_pointerS) + 1);
        arg3K0 = (Scode_pointerS);
        goto L36237;}
      else {
        if ((a_1340X < 0)) {
          if ((b_1341X < 0)) {s48_make_availableAgc(24);
            if ((2305843009213693951 < c_2298X)) {
              goto L68997;}
            else {
              if ((c_2298X < -2305843009213693952)) {
                goto L68997;}
              else {
                arg0K0 = (PS_SHIFT_LEFT_INLINE(c_2298X, 2));
                goto L68992;}}}
          else {
            goto L12542;}}
        else {
          if ((b_1341X < 0)) {
            goto L12542;}
          else {s48_make_availableAgc(24);
            if ((2305843009213693951 < c_2298X)) {
              goto L69019;}
            else {
              if ((c_2298X < -2305843009213693952)) {
                goto L69019;}
              else {
                arg0K0 = (PS_SHIFT_LEFT_INLINE(c_2298X, 2));
                goto L69014;}}}}}}}}
 L69100: {
  v_2526X = (char *) s48_long_to_bignum(c_2303X);
  v_2527X = enter_bignum(v_2526X);
  arg0K0 = v_2527X;
  goto L69095;}
 L69095: {
  val_2528X = arg0K0;
  SvalS = val_2528X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L12776: {
  x_2529X = 0 - c_2303X;s48_make_availableAgc(24);
  if ((2305843009213693951 < x_2529X)) {
    goto L69078;}
  else {
    if ((x_2529X < -2305843009213693952)) {
      goto L69078;}
    else {
      arg0K0 = (PS_SHIFT_LEFT_INLINE(x_2529X, 2));
      goto L69073;}}}
 L69122: {
  v_2530X = (char *) s48_long_to_bignum(c_2303X);
  v_2531X = enter_bignum(v_2530X);
  arg0K0 = v_2531X;
  goto L69117;}
 L69117: {
  val_2532X = arg0K0;
  SvalS = val_2532X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L58805: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2308X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (y_2309X);
  arg0K0 = 2;
  goto L33796;}
 L48531: {
  val_2533X = arg0K0;
  SvalS = val_2533X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L48791: {
  val_2534X = arg0K0;
  SvalS = val_2534X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L49114: {
  val_2535X = arg0K0;
  SvalS = val_2535X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L49437: {
  val_2536X = arg0K0;
  SvalS = val_2536X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L49731: {
  val_2537X = arg0K0;
  SvalS = val_2537X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L13191: {
  if ((2305843009213693951 < c_2325X)) {
    val_2538X = Hinteger_op8731(arg2_1359X, y_1360X);
    SvalS = val_2538X;
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}
  else {
    SvalS = (PS_SHIFT_LEFT_INLINE(c_2325X, 2));
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}}
 L13190: {
  SvalS = (PS_SHIFT_LEFT_INLINE((0 - c_2325X), 2));
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L50241: {
  n_2539X = arg0K0;
  SvalS = (PS_SHIFT_LEFT_INLINE(n_2539X, 2));
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L59132: {
  v_2540X = (char *) s48_long_to_bignum(x_2330X);
  v_2541X = enter_bignum(v_2540X);
  arg0K0 = v_2541X;
  goto L59127;}
 L59127: {
  val_2542X = arg0K0;
  SvalS = val_2542X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L26705: {
  x_2543X = arg3K0;
  v_2544X = s48_bignum_test(x_2543X);
  if ((-1 == v_2544X)) {
    v_2545X = (char *) s48_bignum_negate(x_2543X);
    arg3K0 = v_2545X;
    goto L26707;}
  else {
    arg3K0 = x_2543X;
    goto L26707;}}
 L59243: {
  x_2546X = arg3K0;
  external_bignum_2547X = (char *) s48_bignum_arithmetic_shift(x_2546X, y_2348X);
  v_2548X = s48_bignum_fits_in_word_p(external_bignum_2547X, 62, 1);
  if (v_2548X) {
    n_2549X = s48_bignum_to_long(external_bignum_2547X);
    arg0K0 = (PS_SHIFT_LEFT_INLINE(n_2549X, 2));
    goto L59171;}
  else {
    v_2550X = enter_bignum(external_bignum_2547X);
    arg0K0 = v_2550X;
    goto L59171;}}
 L59177: {
  val_2551X = arg0K0;
  SvalS = val_2551X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L52104: {
  bits_2552X = arg0K0;
  j_2553X = arg0K1;
  shifted_2554X = arg0K2;
  if ((j_2553X < 4)) {
    *((unsigned char *) ((((char *) (-3 + vector_2060X))) + ((PS_SHIFT_LEFT_INLINE(i_2366X, 2)) + j_2553X))) = (unsigned char) ((255 & shifted_2554X));
    arg0K0 = (8 + bits_2552X);
    arg0K1 = (1 + j_2553X);
    arg0K2 = (PS_SHIFT_RIGHT_LOGICAL_INLINE(shifted_2554X, 8));
    goto L52104;}
  else {
    arg0K0 = (-1 + i_2366X);
    goto L52030;}}
 L30771: {
  b_2555X = arg0K0;
  addr_2556X = s48_allocate_small(24);
  *((long *) addr_2556X) = (long) (4102);
  x_2557X = 3 + (((long) (addr_2556X + 8)));
  *((long *) (((char *) (-3 + x_2557X)))) = (long) (string_1507X);
  *((long *) ((((char *) (-3 + x_2557X))) + 8)) = (long) (b_2555X);
  if ((3 == (3 & x_2557X))) {
    arg0K0 = (-4 & x_2557X);
    goto L30777;}
  else {
    arg0K0 = x_2557X;
    goto L30777;}}
 L47834: {
  val_2558X = arg0K0;
  SvalS = val_2558X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L30786: {
  link_2559X = *((long *) ((((char *) (-3 + foo_2367X))) + 8));
  if ((0 == (3 & link_2559X))) {
    arg0K0 = (3 + (-4 & link_2559X));
    goto L30766;}
  else {
    arg0K0 = link_2559X;
    goto L30766;}}
 L52335: {
  if ((1 == (*((Svm_channelsS) + index_2370X)))) {
    channel_2560X = make_channel((PS_SHIFT_LEFT_INLINE(mode_1521X, 2)), arg3_1519X, (PS_SHIFT_LEFT_INLINE(index_2370X, 2)), close_silentlyP_1522X, 1, 1, 1, 0);
    *((Svm_channelsS) + index_2370X) = channel_2560X;
    arg0K0 = channel_2560X;
    arg0K1 = 10;
    goto L52224;}
  else {
    arg0K0 = 1;
    arg0K1 = 12;
    goto L52224;}}
 L52224: {
  channel_2561X = arg0K0;
  reason_2562X = arg0K1;
  if ((1 == channel_2561X)) {
    if ((3 == (3 & arg4_1520X))) {
      if ((17 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + arg4_1520X))))), 2))))) {
        if ((1 == mode_1521X)) {
          goto L52369;}
        else {
          if ((3 == mode_1521X)) {
            goto L52369;}
          else {
            v_2563X = ps_close_fd(index_2370X);
            arg0K0 = v_2563X;
            goto L52364;}}}
      else {push_exception_setupB(reason_2562X, 1);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (arg4_1520X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(mode_1521X, 2)));
        arg0K0 = 2;
        goto L33796;}}
    else {push_exception_setupB(reason_2562X, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (arg4_1520X);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(mode_1521X, 2)));
      arg0K0 = 2;
      goto L33796;}}
  else {
    SvalS = channel_2561X;
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}}
 L52745: {
push_exception_setupB(5, 1);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg5_1530X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (arg4_1529X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(start_2378X, 2)));
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(count_2379X, 2)));
  if (waitP_2377X) {
    arg0K0 = 5;
    goto L52761;}
  else {
    arg0K0 = 1;
    goto L52761;}}
 L52744: {
  val_2564X = arg0K0;
  SvalS = val_2564X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L53316: {
  x_2565X = Scurrent_threadS;
  addr_2566X = (((char *) (-3 + x_2565X))) + 24;S48_WRITE_BARRIER(x_2565X, addr_2566X, proposal_1562X);
  *((long *) addr_2566X) = (long) (proposal_1562X);
  SvalS = 13;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L53667: {
  copies_2567X = arg0K0;
  if ((1 == copies_2567X)) {
    log_2568X = *((long *) ((((char *) (-3 + proposal_1563X))) + 8));
    arg0K0 = 0;
    goto L14476;}
  else {
    thing_2569X = *((long *) ((((char *) (-3 + copies_2567X))) + 16));
    if ((3 == (3 & thing_2569X))) {
      if ((0 == (128 & (*((long *) (((char *) (-11 + thing_2569X)))))))) {
        arg0K0 = (*((long *) ((((char *) (-3 + copies_2567X))) + 40)));
        goto L53667;}
      else {
        goto L53567;}}
    else {
      goto L53567;}}}
 L15067: {
  arg0K0 = (4 + i_2394X);
  goto L15015;}
 L16432: {
  entry_2570X = arg0K0;
  proposal_2571X = *((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24));
  value_2572X = Stemp0S;
  Stemp0S = 1;
  addr_2573X = ((char *) (-3 + entry_2570X));S48_WRITE_BARRIER(entry_2570X, addr_2573X, value_2572X);
  *((long *) addr_2573X) = (long) (value_2572X);
  addr_2574X = (((char *) (-3 + entry_2570X))) + 8;S48_WRITE_BARRIER(entry_2570X, addr_2574X, from_index_2114X);
  *((long *) addr_2574X) = (long) (from_index_2114X);
  value_2575X = Stemp1S;
  Stemp1S = 1;
  addr_2576X = (((char *) (-3 + entry_2570X))) + 16;S48_WRITE_BARRIER(entry_2570X, addr_2576X, value_2575X);
  *((long *) addr_2576X) = (long) (value_2575X);
  addr_2577X = (((char *) (-3 + entry_2570X))) + 24;S48_WRITE_BARRIER(entry_2570X, addr_2577X, to_index_2115X);
  *((long *) addr_2577X) = (long) (to_index_2115X);
  addr_2578X = (((char *) (-3 + entry_2570X))) + 32;S48_WRITE_BARRIER(entry_2570X, addr_2578X, count_2116X);
  *((long *) addr_2578X) = (long) (count_2116X);
  value_2579X = *((long *) ((((char *) (-3 + proposal_2571X))) + 24));
  addr_2580X = (((char *) (-3 + entry_2570X))) + 40;S48_WRITE_BARRIER(entry_2570X, addr_2580X, value_2579X);
  *((long *) addr_2580X) = (long) (value_2579X);
  addr_2581X = (((char *) (-3 + proposal_2571X))) + 24;S48_WRITE_BARRIER(proposal_2571X, addr_2581X, entry_2570X);
  *((long *) addr_2581X) = (long) (entry_2570X);
  SvalS = 13;
  Scode_pointerS = ((Scode_pointerS) + 2);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L62808: {
  SvalS = 13;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L30264: {
  bucket_2582X = arg0K0;
  arg0K0 = 1;
  arg0K1 = bucket_2582X;
  goto L30271;}
 L54205: {
  bits_2583X = arg0K0;
  j_2584X = arg0K1;
  shifted_2585X = arg0K2;
  if ((j_2584X < 4)) {
    *((unsigned char *) ((((char *) (-3 + obj_2170X))) + ((PS_SHIFT_LEFT_INLINE(i_2411X, 2)) + j_2584X))) = (unsigned char) ((255 & shifted_2585X));
    arg0K0 = (8 + bits_2583X);
    arg0K1 = (1 + j_2584X);
    arg0K2 = (PS_SHIFT_RIGHT_LOGICAL_INLINE(shifted_2585X, 8));
    goto L54205;}
  else {
    arg0K0 = (*((long *) ((((char *) (-3 + l_2410X))) + 8)));
    arg0K1 = (-1 + i_2411X);
    goto L54134;}}
 L34493: {
  x_2586X = arg0K0;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2586X);
  arg0K0 = 2;
  arg0K1 = 25;
  arg0K2 = 0;
  goto L33224;}
 L34856: {
  x_2587X = arg0K0;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2587X);
  arg0K0 = 2;
  arg0K1 = 25;
  arg0K2 = 0;
  goto L33224;}
 L43838: {
  encoding_okP_2588X = arg4K0;
  okP_2589X = arg4K1;
  incompleteP_2590X = arg4K2;
  value_2591X = arg0K3;
  count_2592X = arg0K4;
  if (encoding_okP_2588X) {
    if (okP_2589X) {
      if (incompleteP_2590X) {
        val_2593X = PS_SHIFT_LEFT_INLINE(i_2417X, 2);
        addr_2594X = (((char *) (-3 + port_2215X))) + 56;S48_WRITE_BARRIER(port_2215X, addr_2594X, val_2593X);
        *((long *) addr_2594X) = (long) (val_2593X);push_exception_setupB(14, 2);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (port_2215X);
        arg0K0 = 1;
        goto L33796;}
      else {
        if ((1 == (*((long *) ((((char *) (-3 + port_2215X))) + 16))))) {
          goto L43847;}
        else {
          if ((13 == value_2591X)) {
            addr_2595X = (((char *) (-3 + port_2215X))) + 72;S48_WRITE_BARRIER(port_2215X, addr_2595X, 5);
            *((long *) addr_2595X) = (long) (5);
            val_2596X = PS_SHIFT_LEFT_INLINE((i_2417X + count_2592X), 2);
            addr_2597X = (((char *) (-3 + port_2215X))) + 56;S48_WRITE_BARRIER(port_2215X, addr_2597X, val_2596X);
            *((long *) addr_2597X) = (long) (val_2596X);
            SvalS = 2569;
            Scode_pointerS = ((Scode_pointerS) + 2);
            arg3K0 = (Scode_pointerS);
            goto L36237;}
          else {
            if ((10 == value_2591X)) {
              if ((1 == (*((long *) ((((char *) (-3 + port_2215X))) + 72))))) {
                goto L43847;}
              else {
                addr_2598X = (((char *) (-3 + port_2215X))) + 72;S48_WRITE_BARRIER(port_2215X, addr_2598X, 1);
                *((long *) addr_2598X) = (long) (1);
                arg0K0 = (i_2417X + count_2592X);
                goto L43793;}}
            else {
              goto L43847;}}}}}
    else {
      val_2599X = PS_SHIFT_LEFT_INLINE(i_2417X, 2);
      addr_2600X = (((char *) (-3 + port_2215X))) + 56;S48_WRITE_BARRIER(port_2215X, addr_2600X, val_2599X);
      *((long *) addr_2600X) = (long) (val_2599X);push_exception_setupB(14, 2);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (port_2215X);
      arg0K0 = 1;
      goto L33796;}}
  else {push_exception_setupB(5, 2);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (port_2215X);
    arg0K0 = 1;
    goto L33796;}}
 L44486: {
  encoding_okP_2601X = arg4K0;
  okP_2602X = arg4K1;
  incompleteP_2603X = arg4K2;
  value_2604X = arg0K3;
  count_2605X = arg0K4;
  if (encoding_okP_2601X) {
    if (okP_2602X) {
      if (incompleteP_2603X) {push_exception_setupB(14, 2);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (port_2217X);
        arg0K0 = 1;
        goto L33796;}
      else {
        if ((1 == (*((long *) ((((char *) (-3 + port_2217X))) + 16))))) {
          SvalS = (9 + (PS_SHIFT_LEFT_INLINE(value_2604X, 8)));
          Scode_pointerS = ((Scode_pointerS) + 2);
          arg3K0 = (Scode_pointerS);
          goto L36237;}
        else {
          if ((13 == value_2604X)) {
            SvalS = 2569;
            Scode_pointerS = ((Scode_pointerS) + 2);
            arg3K0 = (Scode_pointerS);
            goto L36237;}
          else {
            if ((10 == value_2604X)) {
              if ((1 == (*((long *) ((((char *) (-3 + port_2217X))) + 72))))) {
                SvalS = (9 + (PS_SHIFT_LEFT_INLINE(value_2604X, 8)));
                Scode_pointerS = ((Scode_pointerS) + 2);
                arg3K0 = (Scode_pointerS);
                goto L36237;}
              else {
                arg0K0 = (i_2442X + count_2605X);
                goto L44441;}}
            else {
              SvalS = (9 + (PS_SHIFT_LEFT_INLINE(value_2604X, 8)));
              Scode_pointerS = ((Scode_pointerS) + 2);
              arg3K0 = (Scode_pointerS);
              goto L36237;}}}}}
    else {push_exception_setupB(14, 2);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (port_2217X);
      arg0K0 = 1;
      goto L33796;}}
  else {push_exception_setupB(5, 2);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (port_2217X);
    arg0K0 = 1;
    goto L33796;}}
 L45158: {
  codec_okP_2606X = arg4K0;
  encoding_okP_2607X = arg4K1;
  out_of_spaceP_2608X = arg4K2;
  count_2609X = arg0K3;
  if (codec_okP_2606X) {
    if (encoding_okP_2607X) {
      if (out_of_spaceP_2608X) {push_exception_setupB(14, 2);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (Kchar_2219X);
        SstackS = ((SstackS) + -8);
        *((long *) (SstackS)) = (long) (port_2220X);
        arg0K0 = 2;
        goto L33796;}
      else {
        val_2610X = PS_SHIFT_LEFT_INLINE((i_2223X + count_2609X), 2);
        addr_2611X = (((char *) (-3 + port_2220X))) + 56;S48_WRITE_BARRIER(port_2220X, addr_2611X, val_2610X);
        *((long *) addr_2611X) = (long) (val_2610X);
        SvalS = 13;
        Scode_pointerS = ((Scode_pointerS) + 2);
        arg3K0 = (Scode_pointerS);
        goto L36237;}}
    else {push_exception_setupB(14, 2);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (Kchar_2219X);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (port_2220X);
      arg0K0 = 2;
      goto L33796;}}
  else {push_exception_setupB(5, 2);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (Kchar_2219X);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (port_2220X);
    arg0K0 = 2;
    goto L33796;}}
 L45123: {
  encoding_okP_2612X = arg4K0;
  out_of_spaceP_2613X = arg4K1;
  count_2614X = arg0K2;
  if (encoding_okP_2612X) {
    if (out_of_spaceP_2613X) {push_exception_setupB(14, 2);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (Kchar_2219X);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (port_2220X);
      arg0K0 = 2;
      goto L33796;}
    else {
      val_2615X = PS_SHIFT_LEFT_INLINE((i_2480X + count_2614X), 2);
      addr_2616X = (((char *) (-3 + port_2220X))) + 56;S48_WRITE_BARRIER(port_2220X, addr_2616X, val_2615X);
      *((long *) addr_2616X) = (long) (val_2615X);
      SvalS = 13;
      Scode_pointerS = ((Scode_pointerS) + 2);
      arg3K0 = (Scode_pointerS);
      goto L36237;}}
  else {push_exception_setupB(14, 2);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (Kchar_2219X);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (port_2220X);
    arg0K0 = 2;
    goto L33796;}}
 L32859: {
  Senabled_interruptsS = 0;
  if ((0 == ((Spending_interruptsS) & (Senabled_interruptsS)))) {
    s48_Sstack_limitS = (Sreal_stack_limitS);
    if ((s48_Spending_eventsPS)) {
      s48_Sstack_limitS = (((char *) -1));
      goto L32861;}
    else {
      goto L32861;}}
  else {
    s48_Sstack_limitS = (((char *) -1));
    goto L32861;}}
 L32898: {
  ps_error("interrupt handler is not a closure", 1, i_1827X);
  goto L32859;}
 L17932: {
  n_2617X = Senabled_interruptsS;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(n_2617X, 2)));
  arg0K0 = 2;
  goto L32828;}
 L11516: {
  count_2618X = arg0K0;
  i_2619X = arg0K1;
  offset_2620X = arg0K2;
  if ((0 == count_2618X)) {
    arg0K0 = i_2619X;
    arg0K1 = offset_2620X;
    goto L11499;}
  else {
    value_2621X = *((long *) ((((char *) (-3 + env_2502X))) + (PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + (1 + offset_2620X)))), 3))));
    addr_2622X = (((char *) (-3 + new_env_1863X))) + (PS_SHIFT_LEFT_INLINE(i_2619X, 3));S48_WRITE_BARRIER(new_env_1863X, addr_2622X, value_2621X);
    *((long *) addr_2622X) = (long) (value_2621X);
    arg0K0 = (-1 + count_2618X);
    arg0K1 = (1 + i_2619X);
    arg0K2 = (1 + offset_2620X);
    goto L11516;}}
 L11866: {
  count_2623X = arg0K0;
  i_2624X = arg0K1;
  offset_2625X = arg0K2;
  if ((0 == count_2623X)) {
    arg0K0 = i_2624X;
    arg0K1 = offset_2625X;
    goto L11849;}
  else {
    value_2626X = *((long *) ((((char *) (-3 + env_2507X))) + (PS_SHIFT_LEFT_INLINE(((PS_SHIFT_LEFT_INLINE((*((unsigned char *) ((Scode_pointerS) + (1 + offset_2625X)))), 8)) + (*((unsigned char *) ((Scode_pointerS) + (2 + offset_2625X))))), 3))));
    addr_2627X = (((char *) (-3 + new_env_1874X))) + (PS_SHIFT_LEFT_INLINE(i_2624X, 3));S48_WRITE_BARRIER(new_env_1874X, addr_2627X, value_2626X);
    *((long *) addr_2627X) = (long) (value_2626X);
    arg0K0 = (-1 + count_2623X);
    arg0K1 = (1 + i_2624X);
    arg0K2 = (2 + offset_2625X);
    goto L11866;}}
 L37599: {
  Scode_pointerS = ((Scode_pointerS) + (1 + bytes_used_2281X));
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L56540: {
  SvalS = 1;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L56766: {
  if ((3 == (3 & n_1971X))) {
    if ((11 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + n_1971X))))), 2))))) {push_exception_setupB(5, 1);
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (n_1971X);
      arg0K0 = 1;
      goto L33796;}
    else {
      goto L56770;}}
  else {
    goto L56770;}}
 L68997: {
  v_2628X = (char *) s48_long_to_bignum(c_2298X);
  v_2629X = enter_bignum(v_2628X);
  arg0K0 = v_2629X;
  goto L68992;}
 L68992: {
  val_2630X = arg0K0;
  SvalS = val_2630X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L12542: {
  x_2631X = 0 - c_2298X;s48_make_availableAgc(24);
  if ((2305843009213693951 < x_2631X)) {
    goto L68975;}
  else {
    if ((x_2631X < -2305843009213693952)) {
      goto L68975;}
    else {
      arg0K0 = (PS_SHIFT_LEFT_INLINE(x_2631X, 2));
      goto L68970;}}}
 L69019: {
  v_2632X = (char *) s48_long_to_bignum(c_2298X);
  v_2633X = enter_bignum(v_2632X);
  arg0K0 = v_2633X;
  goto L69014;}
 L69014: {
  val_2634X = arg0K0;
  SvalS = val_2634X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L69078: {
  v_2635X = (char *) s48_long_to_bignum(x_2529X);
  v_2636X = enter_bignum(v_2635X);
  arg0K0 = v_2636X;
  goto L69073;}
 L69073: {
  val_2637X = arg0K0;
  SvalS = val_2637X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L26707: {
  external_bignum_2638X = arg3K0;
  v_2639X = s48_bignum_fits_in_word_p(external_bignum_2638X, 62, 1);
  if (v_2639X) {
    n_2640X = s48_bignum_to_long(external_bignum_2638X);
    arg0K0 = (PS_SHIFT_LEFT_INLINE(n_2640X, 2));
    goto L59109;}
  else {
    val_2641X = enter_bignum(external_bignum_2638X);
    arg0K0 = val_2641X;
    goto L59109;}}
 L59171: {
  val_2642X = arg0K0;
  SvalS = val_2642X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L30777: {
  value_2643X = arg0K0;
  addr_2644X = (((char *) (-3 + table_1506X))) + (PS_SHIFT_LEFT_INLINE(index_1509X, 3));S48_WRITE_BARRIER(table_1506X, addr_2644X, value_2643X);
  *((long *) addr_2644X) = (long) (value_2643X);
  arg0K0 = x_2557X;
  goto L47834;}
 L52369: {
  v_2645X = ps_close_fd(index_2370X);
  arg0K0 = v_2645X;
  goto L52364;}
 L52364: {
  status_2646X = arg0K0;
  if ((status_2646X == NO_ERRORS)) {push_exception_setupB(reason_2562X, 1);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (arg4_1520X);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(mode_1521X, 2)));
    arg0K0 = 2;
    goto L33796;}
  else {channel_close_error(status_2646X, index_2370X, arg4_1520X);push_exception_setupB(reason_2562X, 1);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (arg4_1520X);
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) ((PS_SHIFT_LEFT_INLINE(mode_1521X, 2)));
    arg0K0 = 2;
    goto L33796;}}
 L52761: {
  x_2647X = arg0K0;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2647X);
  arg0K0 = 5;
  goto L33796;}
 L14476: {
  i_2648X = arg0K0;
  stob_2649X = *((long *) ((((char *) (-3 + log_2568X))) + (PS_SHIFT_LEFT_INLINE(i_2648X, 3))));
  if ((1 == stob_2649X)) {
    log_2650X = *((long *) ((((char *) (-3 + proposal_1563X))) + 16));
    arg0K0 = 0;
    goto L16053;}
  else {
    value_2651X = *((long *) ((((char *) (-3 + log_2568X))) + (16 + (PS_SHIFT_LEFT_INLINE(i_2648X, 3)))));
    verify_2652X = *((long *) ((((char *) (-3 + log_2568X))) + (24 + (PS_SHIFT_LEFT_INLINE(i_2648X, 3)))));
    if ((verify_2652X == value_2651X)) {
      goto L14508;}
    else {
      addr_2653X = (((char *) (-3 + stob_2649X))) + (PS_SHIFT_LEFT_INLINE((-4 & (*((long *) ((((char *) (-3 + log_2568X))) + (8 + (PS_SHIFT_LEFT_INLINE(i_2648X, 3))))))), 1));S48_WRITE_BARRIER(stob_2649X, addr_2653X, value_2651X);
      *((long *) addr_2653X) = (long) (value_2651X);
      goto L14508;}}}
 L30271: {
  previous_foo_2654X = arg0K0;
  foo_2655X = arg0K1;
  if ((1 == foo_2655X)) {
    goto L46057;}
  else {
    s2_2656X = *((long *) (((char *) (-3 + foo_2655X))));
    len_2657X = PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + arg2_1669X))))), 8);
    if ((len_2657X == (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + s2_2656X))))), 8)))) {
      if (((!memcmp((void *)(((char *) (-3 + s2_2656X))), (void *)(((char *) (-3 + arg2_1669X))),len_2657X)))) {
        if ((1 == previous_foo_2654X)) {
          value_2658X = *((long *) ((((char *) (-3 + foo_2655X))) + 24));
          addr_2659X = (((char *) (-3 + table_2405X))) + (PS_SHIFT_LEFT_INLINE(index_2407X, 3));S48_WRITE_BARRIER(table_2405X, addr_2659X, value_2658X);
          *((long *) addr_2659X) = (long) (value_2658X);
          goto L46057;}
        else {
          val_2660X = *((long *) ((((char *) (-3 + foo_2655X))) + 24));
          addr_2661X = (((char *) (-3 + previous_foo_2654X))) + 24;S48_WRITE_BARRIER(previous_foo_2654X, addr_2661X, val_2660X);
          *((long *) addr_2661X) = (long) (val_2660X);
          goto L46057;}}
      else {
        goto L30330;}}
    else {
      goto L30330;}}}
 L43847: {
  addr_2662X = (((char *) (-3 + port_2215X))) + 72;S48_WRITE_BARRIER(port_2215X, addr_2662X, 1);
  *((long *) addr_2662X) = (long) (1);
  val_2663X = PS_SHIFT_LEFT_INLINE((i_2417X + count_2592X), 2);
  addr_2664X = (((char *) (-3 + port_2215X))) + 56;S48_WRITE_BARRIER(port_2215X, addr_2664X, val_2663X);
  *((long *) addr_2664X) = (long) (val_2663X);
  SvalS = (9 + (PS_SHIFT_LEFT_INLINE(value_2591X, 8)));
  Scode_pointerS = ((Scode_pointerS) + 2);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L32861: {
  arg0K0 = arg_count_2240X;
  arg0K1 = 25;
  arg0K2 = 0;
  arg0K3 = (-2 - i_1827X);
  goto L66500;}
 L56770: {
  SvalS = 1;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L68975: {
  v_2665X = (char *) s48_long_to_bignum(x_2631X);
  v_2666X = enter_bignum(v_2665X);
  arg0K0 = v_2666X;
  goto L68970;}
 L68970: {
  val_2667X = arg0K0;
  SvalS = val_2667X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L59109: {
  val_2668X = arg0K0;
  SvalS = val_2668X;
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L16053: {
  i_2669X = arg0K0;
  stob_2670X = *((long *) ((((char *) (-3 + log_2650X))) + (PS_SHIFT_LEFT_INLINE(i_2669X, 3))));
  if ((1 == stob_2670X)) {
    copies_2671X = *((long *) ((((char *) (-3 + proposal_1563X))) + 24));
    arg0K0 = copies_2671X;
    goto L15968;}
  else {
    value_2672X = *((long *) ((((char *) (-3 + log_2650X))) + (16 + (PS_SHIFT_LEFT_INLINE(i_2669X, 3)))));
    verify_2673X = *((long *) ((((char *) (-3 + log_2650X))) + (24 + (PS_SHIFT_LEFT_INLINE(i_2669X, 3)))));
    if ((verify_2673X == value_2672X)) {
      goto L16085;}
    else {
      *((unsigned char *) ((((char *) (-3 + stob_2670X))) + (PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + log_2650X))) + (8 + (PS_SHIFT_LEFT_INLINE(i_2669X, 3)))))), 2)))) = (unsigned char) ((PS_SHIFT_RIGHT_INLINE(value_2672X, 2)));
      goto L16085;}}}
 L14508: {
  arg0K0 = (4 + i_2648X);
  goto L14476;}
 L46057: {
  Scode_pointerS = ((Scode_pointerS) + 1);
  arg3K0 = (Scode_pointerS);
  goto L36237;}
 L30330: {
  link_2674X = *((long *) ((((char *) (-3 + foo_2655X))) + 24));
  if ((0 == (3 & link_2674X))) {
    arg0K0 = foo_2655X;
    arg0K1 = (3 + (-4 & link_2674X));
    goto L30271;}
  else {
    arg0K0 = foo_2655X;
    arg0K1 = link_2674X;
    goto L30271;}}
 L15968: {
  copies_2675X = arg0K0;
  if ((1 == copies_2675X)) {
    value_2676X = Sempty_logS;
    addr_2677X = (((char *) (-3 + proposal_1563X))) + 8;S48_WRITE_BARRIER(proposal_1563X, addr_2677X, value_2676X);
    *((long *) addr_2677X) = (long) (value_2676X);
    value_2678X = Sempty_logS;
    addr_2679X = (((char *) (-3 + proposal_1563X))) + 16;S48_WRITE_BARRIER(proposal_1563X, addr_2679X, value_2678X);
    *((long *) addr_2679X) = (long) (value_2678X);
    addr_2680X = (((char *) (-3 + proposal_1563X))) + 24;S48_WRITE_BARRIER(proposal_1563X, addr_2680X, 1);
    *((long *) addr_2680X) = (long) (1);RELEASE_PROPOSAL_LOCK();
    x_2681X = Scurrent_threadS;
    addr_2682X = (((char *) (-3 + x_2681X))) + 24;S48_WRITE_BARRIER(x_2681X, addr_2682X, 1);
    *((long *) addr_2682X) = (long) (1);
    SvalS = 5;
    Scode_pointerS = ((Scode_pointerS) + 1);
    arg3K0 = (Scode_pointerS);
    goto L36237;}
  else {
    stob_2683X = *((long *) ((((char *) (-3 + copies_2675X))) + 16));
    v_2684X = PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + copies_2675X))) + 24))), 2);
    stob_2685X = *((long *) (((char *) (-3 + copies_2675X))));
    v_2686X = PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + copies_2675X))) + 8))), 2);
    v_2687X = PS_SHIFT_RIGHT_INLINE((*((long *) ((((char *) (-3 + copies_2675X))) + 32))), 2);
    memmove((void *)((((char *) (-3 + stob_2683X))) + v_2684X), (void *)((((char *) (-3 + stob_2685X))) + v_2686X),v_2687X);
    arg0K0 = (*((long *) ((((char *) (-3 + copies_2675X))) + 40)));
    goto L15968;}}
 L16085: {
  arg0K0 = (4 + i_2669X);
  goto L16053;}
 use_event_type_uidB: {
  id_1132X = merged_arg0K0;{
  type_2688X = *((Sevent_typesS) + id_1132X);
  v_2689X = type_2688X->usedP;
  if (v_2689X) {
    ps_write_string("trying to use an event uid that's already in use : ", (stderr));
    ps_write_integer(id_1132X, (stderr));
    { long ignoreXX;
    PS_WRITE_CHAR(10, (stderr), ignoreXX) }
    ps_error("assertion violation", 0);
    goto L4126;}
  else {
    goto L4126;}}
 L4126: {
  type_2688X->usedP = 1;
  arg1K0 = (NULL);
  arg1K1 = (Sunused_event_types_headS);
  goto L4133;}
 L4133: {
  previous_2690X = arg1K0;
  unused_type_2691X = arg1K1;
  if ((NULL == unused_type_2691X)) {
    goto L4222;}
  else {
    if ((type_2688X == unused_type_2691X)) {
      if ((NULL == previous_2690X)) {
        Sunused_event_types_headS = (unused_type_2691X->next);
        goto L4222;}
      else {
        previous_2690X->next = (unused_type_2691X->next);
        goto L4222;}}
    else {
      arg1K0 = unused_type_2691X;
      arg1K1 = (unused_type_2691X->next);
      goto L4133;}}}
 L4222: {
  type_2688X->next = (NULL);
#ifdef USE_DIRECT_THREADING
  goto *use_event_type_uidB_return_address;
#else
  goto use_event_type_uidB_return;
#endif
}
#ifndef USE_DIRECT_THREADING
 use_event_type_uidB_return:
  switch (use_event_type_uidB_return_tag) {
  case 0: goto use_event_type_uidB_return_0;
  case 1: goto use_event_type_uidB_return_1;
  case 2: goto use_event_type_uidB_return_2;
  default: goto use_event_type_uidB_return_3;
  }
#endif
}

 move_args_above_contB: {
  nargs_1131X = merged_arg0K0;{
  top_of_args_2692X = SstackS;
  if (((ScontS) == (top_of_args_2692X + (PS_SHIFT_LEFT_INLINE(nargs_1131X, 3))))) {
#ifdef USE_DIRECT_THREADING
    goto *move_args_above_contB_return_address;
#else
    goto move_args_above_contB_return;
#endif
}
  else {
    SstackS = (ScontS);
    arg3K0 = ((SstackS) + -8);
    arg3K1 = (top_of_args_2692X + (-8 + (PS_SHIFT_LEFT_INLINE(nargs_1131X, 3))));
    goto L8658;}}
 L8658: {
  loc_2693X = arg3K0;
  arg_2694X = arg3K1;
  if ((arg_2694X < top_of_args_2692X)) {
    SstackS = ((SstackS) + (0 - (PS_SHIFT_LEFT_INLINE(nargs_1131X, 3))));
#ifdef USE_DIRECT_THREADING
    goto *move_args_above_contB_return_address;
#else
    goto move_args_above_contB_return;
#endif
}
  else {
    *((long *) loc_2693X) = (long) ((*((long *) arg_2694X)));
    arg3K0 = (loc_2693X + -8);
    arg3K1 = (arg_2694X + -8);
    goto L8658;}}
#ifndef USE_DIRECT_THREADING
 move_args_above_contB_return:
  switch (move_args_above_contB_return_tag) {
  case 0: goto move_args_above_contB_return_0;
  case 1: goto move_args_above_contB_return_1;
  case 2: goto move_args_above_contB_return_2;
  case 3: goto move_args_above_contB_return_3;
  case 4: goto move_args_above_contB_return_4;
  case 5: goto move_args_above_contB_return_5;
  case 6: goto move_args_above_contB_return_6;
  case 7: goto move_args_above_contB_return_7;
  case 8: goto move_args_above_contB_return_8;
  case 9: goto move_args_above_contB_return_9;
  default: goto move_args_above_contB_return_10;
  }
#endif
}

 s48_pop_interrupt_state: {
{ p_2695X = *((long *) (SstackS));
  SstackS = ((SstackS) + 8);
  Senabled_interruptsS = (PS_SHIFT_RIGHT_INLINE(p_2695X, 2));
  if ((0 == ((Spending_interruptsS) & (Senabled_interruptsS)))) {
    s48_Sstack_limitS = (Sreal_stack_limitS);
    if ((s48_Spending_eventsPS)) {
      s48_Sstack_limitS = (((char *) -1));
      goto L13719;}
    else {
      goto L13719;}}
  else {
    s48_Sstack_limitS = (((char *) -1));
    goto L13719;}}
 L13719: {
  proposal_2696X = *((long *) (SstackS));
  SstackS = ((SstackS) + 8);
  x_2697X = Scurrent_threadS;
  addr_2698X = (((char *) (-3 + x_2697X))) + 24;S48_WRITE_BARRIER(x_2697X, addr_2698X, proposal_2696X);
  *((long *) addr_2698X) = (long) (proposal_2696X);
#ifdef USE_DIRECT_THREADING
  goto *s48_pop_interrupt_state_return_address;
#else
  goto s48_pop_interrupt_state_return;
#endif
}
#ifndef USE_DIRECT_THREADING
 s48_pop_interrupt_state_return:
  switch (s48_pop_interrupt_state_return_tag) {
  case 0: goto s48_pop_interrupt_state_return_0;
  case 1: goto s48_pop_interrupt_state_return_1;
  default: goto s48_pop_interrupt_state_return_2;
  }
#endif
}

 copy_continuation_from_heapB: {
  cont_1129X = merged_arg0K0;
  stack_arg_count_1130X = merged_arg0K1;{
  stack_size_2699X = -2 + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + cont_1129X))))), 8))), 3));
  new_cont_2700X = (Sbottom_of_stackS) + (0 - (PS_SHIFT_LEFT_INLINE(stack_size_2699X, 3)));
  if ((0 == stack_arg_count_1130X)) {
    SstackS = new_cont_2700X;
    goto L19678;}
  else {
    new_stack_2701X = new_cont_2700X + (0 - (PS_SHIFT_LEFT_INLINE(stack_arg_count_1130X, 3)));
    if ((new_stack_2701X < (SstackS))) {
      memmove((void *)new_stack_2701X, (void *)(SstackS),(PS_SHIFT_LEFT_INLINE(stack_arg_count_1130X, 3)));
      SstackS = new_stack_2701X;
      goto L19678;}
    else {
      goto L19678;}}}
 L19678: {
  ScontS = new_cont_2700X;
  memmove((void *)(new_cont_2700X + 8), (void *)((((char *) (-3 + cont_1129X))) + 24),(-8 + (PS_SHIFT_LEFT_INLINE(stack_size_2699X, 3))));
  *((long *) new_cont_2700X) = (long) ((((long) ((((char *) (-3 + (*((long *) ((((char *) (-3 + cont_1129X))) + 8)))))) + (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-3 + cont_1129X))))), 2))))));
  Sheap_continuationS = (*((long *) ((((char *) (-3 + cont_1129X))) + 16)));
  copy_continuation_from_heapB0_return_value = new_cont_2700X;
#ifdef USE_DIRECT_THREADING
  goto *copy_continuation_from_heapB_return_address;
#else
  goto copy_continuation_from_heapB_return;
#endif
}
#ifndef USE_DIRECT_THREADING
 copy_continuation_from_heapB_return:
  switch (copy_continuation_from_heapB_return_tag) {
  case 0: goto copy_continuation_from_heapB_return_0;
  case 1: goto copy_continuation_from_heapB_return_1;
  default: goto copy_continuation_from_heapB_return_2;
  }
#endif
}

 okay_argument_list: {
  list_1128X = merged_arg0K0;{
  arg0K0 = list_1128X;
  arg0K1 = 0;
  arg0K2 = list_1128X;
  arg4K3 = 0;
  goto L19849;}
 L19849: {
  fast_2702X = arg0K0;
  len_2703X = arg0K1;
  slow_2704X = arg0K2;
  move_slowP_2705X = arg4K3;
  if ((25 == fast_2702X)) {
    okay_argument_list0_return_value = 1;
    okay_argument_list1_return_value = len_2703X;
#ifdef USE_DIRECT_THREADING
    goto *okay_argument_list_return_address;
#else
    goto okay_argument_list_return;
#endif
}
  else {
    if ((3 == (3 & fast_2702X))) {
      if ((0 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + fast_2702X))))), 2))))) {
        if (move_slowP_2705X) {
          if ((fast_2702X == slow_2704X)) {
            okay_argument_list0_return_value = 0;
            okay_argument_list1_return_value = 0;
#ifdef USE_DIRECT_THREADING
            goto *okay_argument_list_return_address;
#else
            goto okay_argument_list_return;
#endif
}
          else {
            arg0K0 = (*((long *) ((((char *) (-3 + fast_2702X))) + 8)));
            arg0K1 = (1 + len_2703X);
            arg0K2 = (*((long *) ((((char *) (-3 + slow_2704X))) + 8)));
            arg4K3 = 0;
            goto L19849;}}
        else {
          arg0K0 = (*((long *) ((((char *) (-3 + fast_2702X))) + 8)));
          arg0K1 = (1 + len_2703X);
          arg0K2 = slow_2704X;
          arg4K3 = 1;
          goto L19849;}}
      else {
        okay_argument_list0_return_value = 0;
        okay_argument_list1_return_value = 0;
#ifdef USE_DIRECT_THREADING
        goto *okay_argument_list_return_address;
#else
        goto okay_argument_list_return;
#endif
}}
    else {
      okay_argument_list0_return_value = 0;
      okay_argument_list1_return_value = 0;
#ifdef USE_DIRECT_THREADING
      goto *okay_argument_list_return_address;
#else
      goto okay_argument_list_return;
#endif
}}}
#ifndef USE_DIRECT_THREADING
 okay_argument_list_return:
  switch (okay_argument_list_return_tag) {
  case 0: goto okay_argument_list_return_0;
  case 1: goto okay_argument_list_return_1;
  default: goto okay_argument_list_return_2;
  }
#endif
}

 get_current_port: {
  marker_1127X = merged_arg0K0;{
  thread_2706X = Scurrent_threadS;
  if ((3 == (3 & thread_2706X))) {
    if ((9 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + thread_2706X))))), 2))))) {
      if ((1 < (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + thread_2706X))))), 8))), 3)))) {
        arg0K0 = (*((long *) ((((char *) (-3 + thread_2706X))) + 8)));
        goto L20095;}
      else {
        goto L20145;}}
    else {
      goto L20145;}}
  else {
    goto L20145;}}
 L20095: {
  env_2707X = arg0K0;
  if ((3 == (3 & env_2707X))) {
    if ((0 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + env_2707X))))), 2))))) {
      obj_2708X = *((long *) (((char *) (-3 + env_2707X))));
      if ((3 == (3 & obj_2708X))) {
        if ((0 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_2708X))))), 2))))) {
          if ((marker_1127X == (*((long *) (((char *) (-3 + (*((long *) (((char *) (-3 + env_2707X)))))))))))) {
            get_current_port0_return_value = (*((long *) ((((char *) (-3 + (*((long *) (((char *) (-3 + env_2707X)))))))) + 8)));
#ifdef USE_DIRECT_THREADING
            goto *get_current_port_return_address;
#else
            goto get_current_port_return;
#endif
}
          else {
            arg0K0 = (*((long *) ((((char *) (-3 + env_2707X))) + 8)));
            goto L20095;}}
        else {
          goto L20167;}}
      else {
        goto L20167;}}
    else {
      goto L20167;}}
  else {
    goto L20167;}}
 L20145: {
  ps_error("current thread is not a record", 0);
  get_current_port0_return_value = v_2709X;
#ifdef USE_DIRECT_THREADING
  goto *get_current_port_return_address;
#else
  goto get_current_port_return;
#endif
}
 L20167: {
  if ((25 == env_2707X)) {
    if (((PS_SHIFT_RIGHT_INLINE(marker_1127X, 2)) == 1)) {
      arg5K0 = "dynamic environment doesn't have current-output-port";
      goto L20121;}
    else {
      arg5K0 = "dynamic environment doesn't have current-input-port";
      goto L20121;}}
  else {
    ps_error("dynamic environment is not a proper list", 0);
#ifdef USE_DIRECT_THREADING
    goto *get_current_port_return_address;
#else
    goto get_current_port_return;
#endif
}}
 L20121: {
  v_2710X = arg5K0;
  ps_error(v_2710X, 0);
#ifdef USE_DIRECT_THREADING
  goto *get_current_port_return_address;
#else
  goto get_current_port_return;
#endif
}
#ifndef USE_DIRECT_THREADING
 get_current_port_return:
  switch (get_current_port_return_tag) {
  case 0: goto get_current_port_return_0;
  case 1: goto get_current_port_return_1;
  case 2: goto get_current_port_return_2;
  case 3: goto get_current_port_return_3;
  case 4: goto get_current_port_return_4;
  default: goto get_current_port_return_5;
  }
#endif
}

 shift_space: {
  x_1125X = merged_arg0K0;
  n_1126X = merged_arg0K1;{
  if ((0 == (3 & x_1125X))) {
    arg0K0 = 1;
    arg0K1 = 3;
    goto L23037;}
  else {
    arg0K0 = (-1 + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + x_1125X))))), 8))), 3)));
    arg0K1 = 0;
    goto L23037;}}
 L23037: {
  x_size_2711X = arg0K0;
  extra_2712X = arg0K1;
  if ((n_1126X < 0)) {
    if ((x_size_2711X < 1)) {
      arg0K0 = 1;
      goto L23079;}
    else {
      arg0K0 = x_size_2711X;
      goto L23079;}}
  else {
    n_2713X = n_1126X / 62;
    arg0K0 = (3 + ((PS_SHIFT_RIGHT_INLINE((15 + (PS_SHIFT_LEFT_INLINE(x_size_2711X, 3))), 3)) + (PS_SHIFT_RIGHT_INLINE((15 + (PS_SHIFT_LEFT_INLINE(n_2713X, 3))), 3))));
    goto L23057;}}
 L23079: {
  v_2714X = arg0K0;
  arg0K0 = (4 + ((-2 & (PS_SHIFT_RIGHT_INLINE((23 + (PS_SHIFT_LEFT_INLINE(v_2714X, 3))), 2))) + (PS_SHIFT_RIGHT_INLINE((15 + (PS_SHIFT_LEFT_INLINE(x_size_2711X, 3))), 3))));
  goto L23057;}
 L23057: {
  v_2715X = arg0K0;
  shift_space0_return_value = (extra_2712X + v_2715X);
#ifdef USE_DIRECT_THREADING
  goto *shift_space_return_address;
#else
  goto shift_space_return;
#endif
}
#ifndef USE_DIRECT_THREADING
 shift_space_return:
  switch (shift_space_return_tag) {
  case 0: goto shift_space_return_0;
  default: goto shift_space_return_1;
  }
#endif
}

 pop_continuationB: {
{ SstackS = (ScontS);
  cont_2716X = ScontS;
  pointer_2717X = (((char *) (*((long *) cont_2716X)))) + -2;
  size_2718X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) pointer_2717X)), 8)) + (*((unsigned char *) (pointer_2717X + 1)));
  if ((65535 == size_2718X)) {
    arg0K0 = (PS_SHIFT_RIGHT_INLINE((*((long *) (cont_2716X + 8))), 2));
    goto L24352;}
  else {
    arg0K0 = size_2718X;
    goto L24352;}}
 L24352: {
  v_2719X = arg0K0;
  ScontS = (cont_2716X + (8 + (PS_SHIFT_LEFT_INLINE(v_2719X, 3))));
  v_2720X = *((long *) (SstackS));
  SstackS = ((SstackS) + 8);
  Scode_pointerS = (((char *) v_2720X));
  Slast_code_pointer_resumedS = (Scode_pointerS);
#ifdef USE_DIRECT_THREADING
  goto *pop_continuationB_return_address;
#else
  goto pop_continuationB_return;
#endif
}
#ifndef USE_DIRECT_THREADING
 pop_continuationB_return:
  switch (pop_continuationB_return_tag) {
  case 0: goto pop_continuationB_return_0;
  case 1: goto pop_continuationB_return_1;
  case 2: goto pop_continuationB_return_2;
  case 3: goto pop_continuationB_return_3;
  case 4: goto pop_continuationB_return_4;
  case 5: goto pop_continuationB_return_5;
  default: goto pop_continuationB_return_6;
  }
#endif
}

 proposal_d_read: {
  stob_1123X = merged_arg0K0;
  index_1124X = merged_arg0K1;{
  log_2721X = *((long *) ((((char *) (-3 + (*((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24)))))) + 8));
  arg0K0 = 0;
  goto L24442;}
 L24442: {
  i_2722X = arg0K0;
  next_stob_2723X = *((long *) ((((char *) (-3 + log_2721X))) + (PS_SHIFT_LEFT_INLINE(i_2722X, 3))));
  if ((1 == next_stob_2723X)) {
    v_2724X = add_log_entryAgc(1, i_2722X, stob_1123X, index_1124X, (*((long *) ((((char *) (-3 + stob_1123X))) + (PS_SHIFT_LEFT_INLINE((-4 & index_1124X), 1))))), 1);
    proposal_d_read0_return_value = v_2724X;
#ifdef USE_DIRECT_THREADING
    goto *proposal_d_read_return_address;
#else
    goto proposal_d_read_return;
#endif
}
  else {
    if ((stob_1123X == next_stob_2723X)) {
      if ((index_1124X == (*((long *) ((((char *) (-3 + log_2721X))) + (8 + (PS_SHIFT_LEFT_INLINE(i_2722X, 3)))))))) {
        proposal_d_read0_return_value = (*((long *) ((((char *) (-3 + log_2721X))) + (16 + (PS_SHIFT_LEFT_INLINE(i_2722X, 3))))));
#ifdef USE_DIRECT_THREADING
        goto *proposal_d_read_return_address;
#else
        goto proposal_d_read_return;
#endif
}
      else {
        goto L24464;}}
    else {
      goto L24464;}}}
 L24464: {
  arg0K0 = (4 + i_2722X);
  goto L24442;}
#ifndef USE_DIRECT_THREADING
 proposal_d_read_return:
  switch (proposal_d_read_return_tag) {
  case 0: goto proposal_d_read_return_0;
  case 1: goto proposal_d_read_return_1;
  default: goto proposal_d_read_return_2;
  }
#endif
}

 proposal_d_write: {
  stob_1120X = merged_arg0K0;
  index_1121X = merged_arg0K1;
  value_1122X = merged_arg0K2;{
  log_2725X = *((long *) ((((char *) (-3 + (*((long *) ((((char *) (-3 + (Scurrent_threadS)))) + 24)))))) + 8));
  arg0K0 = 0;
  goto L24619;}
 L24619: {
  i_2726X = arg0K0;
  next_stob_2727X = *((long *) ((((char *) (-3 + log_2725X))) + (PS_SHIFT_LEFT_INLINE(i_2726X, 3))));
  if ((1 == next_stob_2727X)) {add_log_entryAgc(1, i_2726X, stob_1120X, index_1121X, value_1122X, 0);
#ifdef USE_DIRECT_THREADING
    goto *proposal_d_write_return_address;
#else
    goto proposal_d_write_return;
#endif
}
  else {
    if ((stob_1120X == next_stob_2727X)) {
      if ((index_1121X == (*((long *) ((((char *) (-3 + log_2725X))) + (8 + (PS_SHIFT_LEFT_INLINE(i_2726X, 3)))))))) {
        addr_2728X = (((char *) (-3 + log_2725X))) + (16 + (PS_SHIFT_LEFT_INLINE(i_2726X, 3)));S48_WRITE_BARRIER(log_2725X, addr_2728X, value_1122X);
        *((long *) addr_2728X) = (long) (value_1122X);
#ifdef USE_DIRECT_THREADING
        goto *proposal_d_write_return_address;
#else
        goto proposal_d_write_return;
#endif
}
      else {
        goto L24639;}}
    else {
      goto L24639;}}}
 L24639: {
  arg0K0 = (4 + i_2726X);
  goto L24619;}
#ifndef USE_DIRECT_THREADING
 proposal_d_write_return:
  switch (proposal_d_write_return_tag) {
  case 0: goto proposal_d_write_return_0;
  case 1: goto proposal_d_write_return_1;
  default: goto proposal_d_write_return_2;
  }
#endif
}

 pending_interruptP: {
{ if ((s48_Spending_eventsPS)) {
    s48_Spending_eventsPS = 0;
    goto L25753;}
  else {
    goto L25739;}}
 L25753: {
  type_2729X = s48_get_next_event(&channel_2730X, &status_2731X);
  if ((type_2729X == ALARM_EVENT)) {
    arg0K0 = 1;
    goto L25759;}
  else {
    if ((type_2729X == KEYBOARD_INTERRUPT_EVENT)) {
      arg0K0 = 2;
      goto L25759;}
    else {
      if ((type_2729X == IO_COMPLETION_EVENT)) {enqueue_channelB(channel_2730X, status_2731X, 1);
        arg0K0 = 16;
        goto L25759;}
      else {
        if ((type_2729X == IO_ERROR_EVENT)) {enqueue_channelB(channel_2730X, status_2731X, 5);
          arg0K0 = 16;
          goto L25759;}
        else {
          if ((type_2729X == OS_SIGNAL_EVENT)) {
            arg0K0 = 32;
            goto L25759;}
          else {
            if ((type_2729X == EXTERNAL_EVENT)) {
              arg0K0 = 64;
              goto L25759;}
            else {
              if ((type_2729X == NO_EVENT)) {
                arg0K0 = 0;
                goto L25759;}
              else {
                if ((type_2729X == ERROR_EVENT)) {
                  ps_write_string("OS error while getting event", (stderr));
                  { long ignoreXX;
                  PS_WRITE_CHAR(10, (stderr), ignoreXX) }
                  ps_write_string((ps_error_string(status_2731X)), (stderr));
                  { long ignoreXX;
                  PS_WRITE_CHAR(10, (stderr), ignoreXX) }
                  arg0K0 = 0;
                  goto L25759;}
                else {
                  ps_write_string("unknown type of event", (stderr));
                  { long ignoreXX;
                  PS_WRITE_CHAR(10, (stderr), ignoreXX) }
                  arg0K0 = 0;
                  goto L25759;}}}}}}}}}
 L25739: {
  if ((0 == ((Spending_interruptsS) & (Senabled_interruptsS)))) {
    s48_Sstack_limitS = (Sreal_stack_limitS);
    if ((s48_Spending_eventsPS)) {
      s48_Sstack_limitS = (((char *) -1));
      pending_interruptP0_return_value = 0;
#ifdef USE_DIRECT_THREADING
      goto *pending_interruptP_return_address;
#else
      goto pending_interruptP_return;
#endif
}
    else {
      pending_interruptP0_return_value = 0;
#ifdef USE_DIRECT_THREADING
      goto *pending_interruptP_return_address;
#else
      goto pending_interruptP_return;
#endif
}}
  else {
    pending_interruptP0_return_value = 1;
#ifdef USE_DIRECT_THREADING
    goto *pending_interruptP_return_address;
#else
    goto pending_interruptP_return;
#endif
}}
 L25759: {
  interrupt_bit_2732X = arg0K0;
  Spending_interruptsS = ((Spending_interruptsS) | interrupt_bit_2732X);
  if ((type_2729X == NO_EVENT)) {
    goto L25739;}
  else {
    goto L25753;}}
#ifndef USE_DIRECT_THREADING
 pending_interruptP_return:
  switch (pending_interruptP_return_tag) {
  case 0: goto pending_interruptP_return_0;
  case 1: goto pending_interruptP_return_1;
  case 2: goto pending_interruptP_return_2;
  case 3: goto pending_interruptP_return_3;
  case 4: goto pending_interruptP_return_4;
  case 5: goto pending_interruptP_return_5;
  default: goto pending_interruptP_return_6;
  }
#endif
}

 rest_list_setupAgc: {
  wants_stack_args_1116X = merged_arg0K0;
  stack_arg_count_1117X = merged_arg0K1;
  list_args_1118X = merged_arg0K2;
  list_arg_count_1119X = merged_arg0K3;{
  if ((stack_arg_count_1117X == wants_stack_args_1116X)) {
    merged_arg0K0 = list_args_1118X;
    merged_arg0K1 = list_arg_count_1119X;
#ifdef USE_DIRECT_THREADING
    copy_listSAgc_return_address = &&copy_listSAgc_return_1;
#else
    copy_listSAgc_return_tag = 1;
#endif
    goto copy_listSAgc;
   copy_listSAgc_return_1:
    x_2733X = copy_listSAgc0_return_value;
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (x_2733X);
#ifdef USE_DIRECT_THREADING
    goto *rest_list_setupAgc_return_address;
#else
    goto rest_list_setupAgc_return;
#endif
}
  else {
    if ((stack_arg_count_1117X < wants_stack_args_1116X)) {
      count_2734X = wants_stack_args_1116X - stack_arg_count_1117X;
      merged_arg0K0 = list_args_1118X;
      merged_arg0K1 = count_2734X;
#ifdef USE_DIRECT_THREADING
      push_list_return_address = &&push_list_return_4;
#else
      push_list_return_tag = 4;
#endif
      goto push_list;
     push_list_return_4:
      v_2735X = push_list0_return_value;
      merged_arg0K0 = v_2735X;
      merged_arg0K1 = (list_arg_count_1119X - count_2734X);
#ifdef USE_DIRECT_THREADING
      copy_listSAgc_return_address = &&copy_listSAgc_return_2;
#else
      copy_listSAgc_return_tag = 2;
#endif
      goto copy_listSAgc;
     copy_listSAgc_return_2:
      x_2736X = copy_listSAgc0_return_value;
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_2736X);
#ifdef USE_DIRECT_THREADING
      goto *rest_list_setupAgc_return_address;
#else
      goto rest_list_setupAgc_return;
#endif
}
    else {
      merged_arg0K0 = list_args_1118X;
      merged_arg0K1 = list_arg_count_1119X;
#ifdef USE_DIRECT_THREADING
      copy_listSAgc_return_address = &&copy_listSAgc_return_3;
#else
      copy_listSAgc_return_tag = 3;
#endif
      goto copy_listSAgc;
     copy_listSAgc_return_3:
      v_2737X = copy_listSAgc0_return_value;
      merged_arg0K0 = v_2737X;
      merged_arg0K1 = (stack_arg_count_1117X - wants_stack_args_1116X);
#ifdef USE_DIRECT_THREADING
      pop_args_GlistSAgc_return_address = &&pop_args_GlistSAgc_return_12;
#else
      pop_args_GlistSAgc_return_tag = 12;
#endif
      goto pop_args_GlistSAgc;
     pop_args_GlistSAgc_return_12:
      x_2738X = pop_args_GlistSAgc0_return_value;
      SstackS = ((SstackS) + -8);
      *((long *) (SstackS)) = (long) (x_2738X);
#ifdef USE_DIRECT_THREADING
      goto *rest_list_setupAgc_return_address;
#else
      goto rest_list_setupAgc_return;
#endif
}}}
#ifndef USE_DIRECT_THREADING
 rest_list_setupAgc_return:
  switch (rest_list_setupAgc_return_tag) {
  case 0: goto rest_list_setupAgc_return_0;
  default: goto rest_list_setupAgc_return_1;
  }
#endif
}

 copy_listSAgc: {
  list_1114X = merged_arg0K0;
  length_1115X = merged_arg0K1;{
  if ((0 == length_1115X)) {
    copy_listSAgc0_return_value = 25;
#ifdef USE_DIRECT_THREADING
    goto *copy_listSAgc_return_address;
#else
    goto copy_listSAgc_return;
#endif
}
  else {
    Stemp0S = list_1114X;s48_make_availableAgc((PS_SHIFT_LEFT_INLINE((3 * length_1115X), 3)));
    value_2739X = Stemp0S;
    Stemp0S = 1;
    a_2740X = *((long *) (((char *) (-3 + value_2739X))));
    addr_2741X = s48_allocate_small(24);
    *((long *) addr_2741X) = (long) (4098);
    x_2742X = 3 + (((long) (addr_2741X + 8)));
    *((long *) (((char *) (-3 + x_2742X)))) = (long) (a_2740X);
    *((long *) ((((char *) (-3 + x_2742X))) + 8)) = (long) (25);
    arg0K0 = (*((long *) ((((char *) (-3 + value_2739X))) + 8)));
    arg0K1 = x_2742X;
    goto L24880;}}
 L24880: {
  l_2743X = arg0K0;
  last_2744X = arg0K1;
  if ((25 == l_2743X)) {
    copy_listSAgc0_return_value = x_2742X;
#ifdef USE_DIRECT_THREADING
    goto *copy_listSAgc_return_address;
#else
    goto copy_listSAgc_return;
#endif
}
  else {
    a_2745X = *((long *) (((char *) (-3 + l_2743X))));
    addr_2746X = s48_allocate_small(24);
    *((long *) addr_2746X) = (long) (4098);
    x_2747X = 3 + (((long) (addr_2746X + 8)));
    *((long *) (((char *) (-3 + x_2747X)))) = (long) (a_2745X);
    *((long *) ((((char *) (-3 + x_2747X))) + 8)) = (long) (25);
    addr_2748X = (((char *) (-3 + last_2744X))) + 8;S48_WRITE_BARRIER(last_2744X, addr_2748X, x_2747X);
    *((long *) addr_2748X) = (long) (x_2747X);
    arg0K0 = (*((long *) ((((char *) (-3 + l_2743X))) + 8)));
    arg0K1 = x_2747X;
    goto L24880;}}
#ifndef USE_DIRECT_THREADING
 copy_listSAgc_return:
  switch (copy_listSAgc_return_tag) {
  case 0: goto copy_listSAgc_return_0;
  case 1: goto copy_listSAgc_return_1;
  case 2: goto copy_listSAgc_return_2;
  default: goto copy_listSAgc_return_3;
  }
#endif
}

 pop_args_GlistSAgc: {
  start_1112X = merged_arg0K0;
  count_1113X = merged_arg0K1;{
  Stemp0S = start_1112X;s48_make_availableAgc((PS_SHIFT_LEFT_INLINE((3 * count_1113X), 3)));
  value_2749X = Stemp0S;
  Stemp0S = 1;
  arg0K0 = value_2749X;
  arg0K1 = count_1113X;
  goto L24992;}
 L24992: {
  args_2750X = arg0K0;
  count_2751X = arg0K1;
  if ((0 == count_2751X)) {
    pop_args_GlistSAgc0_return_value = args_2750X;
#ifdef USE_DIRECT_THREADING
    goto *pop_args_GlistSAgc_return_address;
#else
    goto pop_args_GlistSAgc_return;
#endif
}
  else {
    a_2752X = *((long *) (SstackS));
    SstackS = ((SstackS) + 8);
    addr_2753X = s48_allocate_small(24);
    *((long *) addr_2753X) = (long) (4098);
    x_2754X = 3 + (((long) (addr_2753X + 8)));
    *((long *) (((char *) (-3 + x_2754X)))) = (long) (a_2752X);
    *((long *) ((((char *) (-3 + x_2754X))) + 8)) = (long) (args_2750X);
    arg0K0 = x_2754X;
    arg0K1 = (-1 + count_2751X);
    goto L24992;}}
#ifndef USE_DIRECT_THREADING
 pop_args_GlistSAgc_return:
  switch (pop_args_GlistSAgc_return_tag) {
  case 0: goto pop_args_GlistSAgc_return_0;
  case 1: goto pop_args_GlistSAgc_return_1;
  case 2: goto pop_args_GlistSAgc_return_2;
  case 3: goto pop_args_GlistSAgc_return_3;
  case 4: goto pop_args_GlistSAgc_return_4;
  case 5: goto pop_args_GlistSAgc_return_5;
  case 6: goto pop_args_GlistSAgc_return_6;
  case 7: goto pop_args_GlistSAgc_return_7;
  case 8: goto pop_args_GlistSAgc_return_8;
  case 9: goto pop_args_GlistSAgc_return_9;
  case 10: goto pop_args_GlistSAgc_return_10;
  case 11: goto pop_args_GlistSAgc_return_11;
  default: goto pop_args_GlistSAgc_return_12;
  }
#endif
}

 push_list: {
  list_1110X = merged_arg0K0;
  count_1111X = merged_arg0K1;{
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (list_1110X);
  merged_arg0K0 = count_1111X;
#ifdef USE_DIRECT_THREADING
  ensure_stack_spaceB_return_address = &&ensure_stack_spaceB_return_2;
#else
  ensure_stack_spaceB_return_tag = 2;
#endif
  goto ensure_stack_spaceB;
 ensure_stack_spaceB_return_2:
  v_2755X = ensure_stack_spaceB0_return_value;
  if (v_2755X) {
    s48_Sstack_limitS = (((char *) -1));
    goto L32135;}
  else {
    goto L32135;}}
 L32135: {
  list_2756X = *((long *) (SstackS));
  SstackS = ((SstackS) + 8);
  arg0K0 = count_1111X;
  arg0K1 = list_2756X;
  goto L32144;}
 L32144: {
  i_2757X = arg0K0;
  l_2758X = arg0K1;
  if ((0 < i_2757X)) {
    x_2759X = *((long *) (((char *) (-3 + l_2758X))));
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (x_2759X);
    arg0K0 = (-1 + i_2757X);
    arg0K1 = (*((long *) ((((char *) (-3 + l_2758X))) + 8)));
    goto L32144;}
  else {
    push_list0_return_value = l_2758X;
#ifdef USE_DIRECT_THREADING
    goto *push_list_return_address;
#else
    goto push_list_return;
#endif
}}
#ifndef USE_DIRECT_THREADING
 push_list_return:
  switch (push_list_return_tag) {
  case 0: goto push_list_return_0;
  case 1: goto push_list_return_1;
  case 2: goto push_list_return_2;
  case 3: goto push_list_return_3;
  default: goto push_list_return_4;
  }
#endif
}

 ensure_stack_spaceB: {
  need_1109X = merged_arg0K0;{
  if ((((SstackS) + (512 - (PS_SHIFT_LEFT_INLINE(need_1109X, 3)))) < (s48_Sstack_limitS))) {
    interruptP_2760X = (s48_Sstack_limitS) == (((char *) -1));
    s48_Sstack_limitS = (Sreal_stack_limitS);
    if ((((SstackS) + (512 - (PS_SHIFT_LEFT_INLINE(need_1109X, 3)))) < (Sreal_stack_limitS))) {s48_copy_stack_into_heap();
      if ((((SstackS) + (512 - (PS_SHIFT_LEFT_INLINE(need_1109X, 3)))) < (Sreal_stack_limitS))) {
        ps_error("VM's stack is too small (how can this happen?)", 0);
        ensure_stack_spaceB0_return_value = interruptP_2760X;
#ifdef USE_DIRECT_THREADING
        goto *ensure_stack_spaceB_return_address;
#else
        goto ensure_stack_spaceB_return;
#endif
}
      else {
        ensure_stack_spaceB0_return_value = interruptP_2760X;
#ifdef USE_DIRECT_THREADING
        goto *ensure_stack_spaceB_return_address;
#else
        goto ensure_stack_spaceB_return;
#endif
}}
    else {
      ensure_stack_spaceB0_return_value = interruptP_2760X;
#ifdef USE_DIRECT_THREADING
      goto *ensure_stack_spaceB_return_address;
#else
      goto ensure_stack_spaceB_return;
#endif
}}
  else {
    ensure_stack_spaceB0_return_value = 0;
#ifdef USE_DIRECT_THREADING
    goto *ensure_stack_spaceB_return_address;
#else
    goto ensure_stack_spaceB_return;
#endif
}}
#ifndef USE_DIRECT_THREADING
 ensure_stack_spaceB_return:
  switch (ensure_stack_spaceB_return_tag) {
  case 0: goto ensure_stack_spaceB_return_0;
  case 1: goto ensure_stack_spaceB_return_1;
  default: goto ensure_stack_spaceB_return_2;
  }
#endif
}

 unused_event_type_uid: {
{ goto L70993;}
 L70993: {
  if ((NULL == (Sunused_event_types_headS))) {
    v_2761X = add_external_event_types((PS_SHIFT_LEFT_INLINE((Snumber_of_event_typesS), 1)));
    if (v_2761X) {
      goto L70993;}
    else {
      unused_event_type_uid0_return_value = -1;
#ifdef USE_DIRECT_THREADING
      goto *unused_event_type_uid_return_address;
#else
      goto unused_event_type_uid_return;
#endif
}}
  else {
    unused_event_type_uid0_return_value = ((Sunused_event_types_headS)->uid);
#ifdef USE_DIRECT_THREADING
    goto *unused_event_type_uid_return_address;
#else
    goto unused_event_type_uid_return;
#endif
}}
#ifndef USE_DIRECT_THREADING
 unused_event_type_uid_return:
  switch (unused_event_type_uid_return_tag) {
  case 0: goto unused_event_type_uid_return_0;
  default: goto unused_event_type_uid_return_1;
  }
#endif
}

 loseD0: {
  message_1108X = merged_arg5K0;{
  ps_write_string("Template UIDs: ", (stderr));
  current_code_2762X = current_code_vector();
  out_2763X = stderr;
  merged_arg3K0 = (SstackS);
  merged_arg0K1 = (PS_SHIFT_RIGHT_INLINE(((ScontS) - (SstackS)), 3));
  merged_arg0K2 = current_code_2762X;
#ifdef USE_DIRECT_THREADING
  find_template_return_address = &&find_template_return_0;
#else
  find_template_return_tag = 0;
#endif
  goto find_template;
 find_template_return_0:
  template_2764X = find_template0_return_value;
  merged_arg0K0 = template_2764X;
  merged_arg4K1 = 0;
  merged_arg6K2 = out_2763X;
#ifdef USE_DIRECT_THREADING
  maybe_write_template_return_address = &&maybe_write_template_return_0;
#else
  maybe_write_template_return_tag = 0;
#endif
  goto maybe_write_template;
 maybe_write_template_return_0:
  not_firstP_2765X = maybe_write_template0_return_value;
  arg3K0 = (ScontS);
  arg4K1 = not_firstP_2765X;
  goto L30216;}
 L30216: {
  cont_2766X = arg3K0;
  not_firstP_2767X = arg4K1;
  if ((cont_2766X == (Sbottom_of_stackS))) {
    cont_2768X = Sheap_continuationS;
    arg0K0 = cont_2768X;
    arg4K1 = not_firstP_2767X;
    goto L29448;}
  else {
    code_pointer_2769X = ((char *) (*((long *) cont_2766X)));
    pointer_2770X = code_pointer_2769X + -5;
    v_2771X = 3 + (((long) (code_pointer_2769X + (0 - ((PS_SHIFT_LEFT_INLINE((*((unsigned char *) pointer_2770X)), 8)) + (*((unsigned char *) (pointer_2770X + 1))))))));
    pointer_2772X = (((char *) (*((long *) cont_2766X)))) + -2;
    size_2773X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) pointer_2772X)), 8)) + (*((unsigned char *) (pointer_2772X + 1)));
    if ((65535 == size_2773X)) {
      arg0K0 = (PS_SHIFT_RIGHT_INLINE((*((long *) (cont_2766X + 8))), 2));
      goto L23821;}
    else {
      arg0K0 = size_2773X;
      goto L23821;}}}
 L29448: {
  cont_2774X = arg0K0;
  not_firstP_2775X = arg4K1;
  if ((3 == (3 & cont_2774X))) {
    if ((10 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + cont_2774X))))), 2))))) {
      merged_arg3K0 = (((char *) (-3 + cont_2774X)));
      merged_arg0K1 = (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_RIGHT_LOGICAL_INLINE((*((long *) (((char *) (-11 + cont_2774X))))), 8))), 3));
      merged_arg0K2 = (*((long *) ((((char *) (-3 + cont_2774X))) + 8)));
#ifdef USE_DIRECT_THREADING
      find_template_return_address = &&find_template_return_1;
#else
      find_template_return_tag = 1;
#endif
      goto find_template;
     find_template_return_1:
      v_2776X = find_template0_return_value;
      merged_arg0K0 = v_2776X;
      merged_arg4K1 = not_firstP_2775X;
      merged_arg6K2 = out_2763X;
#ifdef USE_DIRECT_THREADING
      maybe_write_template_return_address = &&maybe_write_template_return_1;
#else
      maybe_write_template_return_tag = 1;
#endif
      goto maybe_write_template;
     maybe_write_template_return_1:
      v_2777X = maybe_write_template0_return_value;
      arg0K0 = (*((long *) ((((char *) (-3 + cont_2774X))) + 16)));
      arg4K1 = v_2777X;
      goto L29448;}
    else {
      goto L33894;}}
  else {
    goto L33894;}}
 L23821: {
  v_2778X = arg0K0;
  merged_arg3K0 = (cont_2766X + 8);
  merged_arg0K1 = v_2778X;
  merged_arg0K2 = v_2771X;
#ifdef USE_DIRECT_THREADING
  find_template_return_address = &&find_template_return_2;
#else
  find_template_return_tag = 2;
#endif
  goto find_template;
 find_template_return_2:
  v_2779X = find_template0_return_value;
  merged_arg0K0 = v_2779X;
  merged_arg4K1 = not_firstP_2767X;
  merged_arg6K2 = out_2763X;
#ifdef USE_DIRECT_THREADING
  maybe_write_template_return_address = &&maybe_write_template_return_2;
#else
  maybe_write_template_return_tag = 2;
#endif
  goto maybe_write_template;
 maybe_write_template_return_2:
  v_2780X = maybe_write_template0_return_value;
  pointer_2781X = (((char *) (*((long *) cont_2766X)))) + -2;
  size_2782X = (PS_SHIFT_LEFT_INLINE((*((unsigned char *) pointer_2781X)), 8)) + (*((unsigned char *) (pointer_2781X + 1)));
  if ((65535 == size_2782X)) {
    arg0K0 = (PS_SHIFT_RIGHT_INLINE((*((long *) (cont_2766X + 8))), 2));
    goto L30234;}
  else {
    arg0K0 = size_2782X;
    goto L30234;}}
 L33894: {
  { long ignoreXX;
  PS_WRITE_CHAR(10, (stderr), ignoreXX) }
  why_2783X = PS_SHIFT_RIGHT_INLINE((*((long *) ((SstackS) + (PS_SHIFT_LEFT_INLINE(nargs_1169X, 3))))), 2);
  if ((why_2783X == 1)) {
    if ((0 == (3 & (*((long *) (((char *) (-3 + (*((long *) ((SstackS) + (-8 + (PS_SHIFT_LEFT_INLINE(nargs_1169X, 3)))))))))))))) {
      ps_error(message_1108X, 3, opcode_1170X, why_2783X, (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-3 + (*((long *) ((SstackS) + (-8 + (PS_SHIFT_LEFT_INLINE(nargs_1169X, 3))))))))))), 2)));
#ifdef USE_DIRECT_THREADING
      goto *loseD0_return_address;
#else
      goto loseD0_return;
#endif
}
    else {
      goto L33841;}}
  else {
    goto L33841;}}
 L30234: {
  v_2784X = arg0K0;
  arg3K0 = (cont_2766X + (8 + (PS_SHIFT_LEFT_INLINE(v_2784X, 3))));
  arg4K1 = v_2780X;
  goto L30216;}
 L33841: {
  ps_error(message_1108X, 2, opcode_1170X, why_2783X);
#ifdef USE_DIRECT_THREADING
  goto *loseD0_return_address;
#else
  goto loseD0_return;
#endif
}
#ifndef USE_DIRECT_THREADING
 loseD0_return:
  switch (loseD0_return_tag) {
  case 0: goto loseD0_return_0;
  default: goto loseD0_return_1;
  }
#endif
}

 find_template: {
  start_1105X = merged_arg3K0;
  count_1106X = merged_arg0K1;
  code_vector_1107X = merged_arg0K2;{
  arg0K0 = 0;
  goto L20550;}
 L20550: {
  i_2785X = arg0K0;
  if ((i_2785X == count_1106X)) {
    find_template0_return_value = 1;
#ifdef USE_DIRECT_THREADING
    goto *find_template_return_address;
#else
    goto find_template_return;
#endif
}
  else {
    next_2786X = *((long *) (start_1105X + (PS_SHIFT_LEFT_INLINE(i_2785X, 3))));
    if ((3 == (3 & next_2786X))) {
      if ((12 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + next_2786X))))), 2))))) {
        if (((*((long *) (((char *) (-3 + next_2786X))))) == code_vector_1107X)) {
          find_template0_return_value = next_2786X;
#ifdef USE_DIRECT_THREADING
          goto *find_template_return_address;
#else
          goto find_template_return;
#endif
}
        else {
          goto L20572;}}
      else {
        goto L20572;}}
    else {
      goto L20572;}}}
 L20572: {
  arg0K0 = (1 + i_2785X);
  goto L20550;}
#ifndef USE_DIRECT_THREADING
 find_template_return:
  switch (find_template_return_tag) {
  case 0: goto find_template_return_0;
  case 1: goto find_template_return_1;
  default: goto find_template_return_2;
  }
#endif
}

 maybe_write_template: {
  template_1102X = merged_arg0K0;
  not_firstP_1103X = merged_arg4K1;
  out_1104X = merged_arg6K2;{
  if (not_firstP_1103X) {
    ps_write_string(" <- ", out_1104X);
    goto L25912;}
  else {
    goto L25912;}}
 L25912: {
  if ((3 == (3 & template_1102X))) {
    if ((12 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + template_1102X))))), 2))))) {
      name_2787X = *((long *) ((((char *) (-3 + template_1102X))) + 16));
      if ((0 == (3 & name_2787X))) {
        ps_write_integer((PS_SHIFT_RIGHT_INLINE(name_2787X, 2)), out_1104X);
        maybe_write_template0_return_value = 1;
#ifdef USE_DIRECT_THREADING
        goto *maybe_write_template_return_address;
#else
        goto maybe_write_template_return;
#endif
}
      else {
        if ((3 == (3 & name_2787X))) {
          if ((9 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + name_2787X))))), 2))))) {
            obj_2788X = *((long *) ((((char *) (-3 + name_2787X))) + 16));
            if ((3 == (3 & obj_2788X))) {
              if ((16 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_2788X))))), 2))))) {write_vm_string((*((long *) ((((char *) (-3 + name_2787X))) + 16))), out_1104X);
                maybe_write_template0_return_value = 1;
#ifdef USE_DIRECT_THREADING
                goto *maybe_write_template_return_address;
#else
                goto maybe_write_template_return;
#endif
}
              else {
                goto L25947;}}
            else {
              goto L25947;}}
          else {
            goto L25947;}}
        else {
          goto L25947;}}}
    else {
      goto L25970;}}
  else {
    goto L25970;}}
 L25947: {
  if ((3 == (3 & name_2787X))) {
    if ((9 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + name_2787X))))), 2))))) {
      obj_2789X = *((long *) ((((char *) (-3 + name_2787X))) + 16));
      if ((3 == (3 & obj_2789X))) {
        if ((1 == (31 & (PS_SHIFT_RIGHT_INLINE((*((long *) (((char *) (-11 + obj_2789X))))), 2))))) {write_vm_string((*((long *) (((char *) (-3 + (*((long *) ((((char *) (-3 + name_2787X))) + 16)))))))), out_1104X);
          maybe_write_template0_return_value = 1;
#ifdef USE_DIRECT_THREADING
          goto *maybe_write_template_return_address;
#else
          goto maybe_write_template_return;
#endif
}
        else {
          goto L25967;}}
      else {
        goto L25967;}}
    else {
      goto L25967;}}
  else {
    goto L25967;}}
 L25970: {
  ps_write_string(" ?? ", out_1104X);
  maybe_write_template0_return_value = 1;
#ifdef USE_DIRECT_THREADING
  goto *maybe_write_template_return_address;
#else
  goto maybe_write_template_return;
#endif
}
 L25967: {
  ps_write_string("?", out_1104X);
  maybe_write_template0_return_value = 1;
#ifdef USE_DIRECT_THREADING
  goto *maybe_write_template_return_address;
#else
  goto maybe_write_template_return;
#endif
}
#ifndef USE_DIRECT_THREADING
 maybe_write_template_return:
  switch (maybe_write_template_return_tag) {
  case 0: goto maybe_write_template_return_0;
  case 1: goto maybe_write_template_return_1;
  default: goto maybe_write_template_return_2;
  }
#endif
}

}
long s48_call_startup_procedure(char **startup_vector_2790X, long startup_vector_length_2791X)
{
  long arg0K2;
  long arg0K1;
  long arg0K0;
  long merged_arg0K1;
  char *merged_arg5K0;

#ifdef USE_DIRECT_THREADING
  void *enter_string_return_address;
#else
  int enter_string_return_tag;
#endif
  long enter_string0_return_value;
  char *string_2792X;
  long shifted_2849X;
  long j_2848X;
  long bits_2847X;
  long c_2846X;
  long i_2845X;
  long s_2844X;
  char * addr_2843X;
  long len_2842X;
  long len_2841X;
  long v_2840X;
  long x_2839X;
  long error_encoding_2838X;
  long output_encoding_2837X;
  long input_encoding_2836X;
  long vm_channel_2835X;
  long v_2834X;
  long channel_2833X;
  long vm_channel_2832X;
  long v_2831X;
  long channel_2830X;
  long vm_channel_2829X;
  long v_2828X;
  long channel_2827X;
  char *error_encoding_2826X;
  long v_2825X;
  char *input_encoding_2824X;
  long v_2823X;
  char *output_encoding_2822X;
  long v_2821X;
  long i_2820X;
  long length_2819X;
  long *v_2818X;
  long v_2817X;
  long v_2816X;
  long y_2815X;
  long x_2814X;
  long v_2813X;
  char * addr_2812X;
  long i_2811X;
  long x_2810X;
  long y_2809X;
  long vec_2808X;
  char * addr_2807X;
  long length_2806X;
  long len_2805X;
  char *s_2804X;
  long y_2803X;
  long x_2802X;
  long i_2801X;
  long vector_2800X;
  char * addr_2799X;
  long len_2798X;
  long count_2797X;
  long i_2796X;
  long code_2795X;
  long code_2794X;
  long code_2793X;
 {  SstackS = (Sbottom_of_stackS);
  Sheap_continuationS = 1;
  ScontS = (Sbottom_of_stackS);
  code_2793X = Sinterrupted_byte_opcode_return_codeS;
  Slast_code_calledS = code_2793X;
  Scode_pointerS = (((char *) (-3 + code_2793X)));
  code_2794X = Sinterrupted_native_call_return_codeS;
  Slast_code_calledS = code_2794X;
  Scode_pointerS = (((char *) (-3 + code_2794X)));
  code_2795X = Snative_poll_return_codeS;
  Slast_code_calledS = code_2795X;
  Scode_pointerS = (((char *) (-3 + code_2795X)));
  Slast_code_pointer_resumedS = (Scode_pointerS);
  SvalS = 13;
  Scurrent_threadS = 25;SHARED_SETB((Ssession_dataS), 25);SHARED_SETB((Sexception_handlersS), 25);SHARED_SETB((Sinterrupt_handlersS), 25);
  Senabled_interruptsS = 0;SHARED_SETB((Sfinalizer_alistS), 25);
  Sfinalize_theseS = 25;
  Spending_interruptsS = 0;
  s48_Spending_interruptPS = 0;
  Sos_signal_ring_startS = 0;
  Sos_signal_ring_readyS = 0;
  Sos_signal_ring_endS = 0;
  Sinterrupted_templateS = 1;
  s48_Snc_templateS = 1;
  arg0K0 = 0;
  arg0K1 = 0;
  goto L22070;}
 L22070: {
  i_2796X = arg0K0;
  count_2797X = arg0K1;
  if ((i_2796X == startup_vector_length_2791X)) {s48_make_availableAgc((PS_SHIFT_LEFT_INLINE((((1 + startup_vector_length_2791X) + startup_vector_length_2791X) + (PS_SHIFT_RIGHT_INLINE((7 + count_2797X), 3))), 3)));
    len_2798X = PS_SHIFT_LEFT_INLINE(startup_vector_length_2791X, 3);
    addr_2799X = s48_allocate_small((8 + len_2798X));
    *((long *) addr_2799X) = (long) ((10 + (PS_SHIFT_LEFT_INLINE(len_2798X, 8))));
    vector_2800X = 3 + (((long) (addr_2799X + 8)));
    arg0K0 = 0;
    goto L22187;}
  else {
    arg0K0 = (1 + i_2796X);
    arg0K1 = (1 + (count_2797X + (strlen((char *) (*(startup_vector_2790X + i_2796X))))));
    goto L22070;}}
 L22187: {
  i_2801X = arg0K0;
  if ((i_2801X == startup_vector_length_2791X)) {
    SstackS = ((SstackS) + -8);
    *((long *) (SstackS)) = (long) (vector_2800X);
    x_2802X = STDOUT_FD();
    y_2803X = STDERR_FD();
    if ((x_2802X < y_2803X)) {
      arg0K0 = y_2803X;
      goto L29148;}
    else {
      arg0K0 = x_2802X;
      goto L29148;}}
  else {
    s_2804X = *(startup_vector_2790X + i_2801X);
    len_2805X = strlen((char *) s_2804X);
    length_2806X = 1 + len_2805X;
    addr_2807X = s48_allocate_small((8 + length_2806X));
    *((long *) addr_2807X) = (long) ((70 + (PS_SHIFT_LEFT_INLINE(length_2806X, 8))));
    vec_2808X = 3 + (((long) (addr_2807X + 8)));
    arg0K0 = 0;
    goto L22207;}}
 L29148: {
  y_2809X = arg0K0;
  x_2810X = STDIN_FD();
  if ((x_2810X < y_2809X)) {
    arg0K0 = y_2809X;
    goto L29150;}
  else {
    arg0K0 = x_2810X;
    goto L29150;}}
 L22207: {
  i_2811X = arg0K0;
  if ((len_2805X < i_2811X)) {
    addr_2812X = (((char *) (-3 + vector_2800X))) + (PS_SHIFT_LEFT_INLINE(i_2801X, 3));S48_WRITE_BARRIER(vector_2800X, addr_2812X, vec_2808X);
    *((long *) addr_2812X) = (long) (vec_2808X);
    arg0K0 = (1 + i_2801X);
    goto L22187;}
  else {
    *((unsigned char *) ((((char *) (-3 + vec_2808X))) + i_2811X)) = (unsigned char) ((((unsigned char) (*(s_2804X + i_2811X)))));
    arg0K0 = (1 + i_2811X);
    goto L22207;}}
 L29150: {
  v_2813X = arg0K0;
  x_2814X = Snumber_of_channelsS;
  y_2815X = 1 + v_2813X;
  if ((x_2814X < y_2815X)) {
    arg0K0 = y_2815X;
    goto L29152;}
  else {
    arg0K0 = x_2814X;
    goto L29152;}}
 L29152: {
  v_2816X = arg0K0;
  Snumber_of_channelsS = v_2816X;
  v_2817X = STDIN_FD();
  Svm_channelsS = ((long*)malloc(sizeof(long) * (Snumber_of_channelsS)));
  Spending_channels_headS = 1;
  Spending_channels_tailS = 1;
  if ((NULL == (Svm_channelsS))) {
    ps_error("out of memory, unable to continue", 0);
    goto L29174;}
  else {
    goto L29174;}}
 L29174: {
  v_2818X = Svm_channelsS;
  length_2819X = Snumber_of_channelsS;
  arg0K0 = 0;
  goto L29274;}
 L29274: {
  i_2820X = arg0K0;
  if ((i_2820X < length_2819X)) {
    *(v_2818X + i_2820X) = 1;
    arg0K0 = (1 + i_2820X);
    goto L29274;}
  else {
    v_2821X = STDOUT_FD();
    output_encoding_2822X = ps_console_encoding(v_2821X);
    v_2823X = STDIN_FD();
    input_encoding_2824X = ps_console_encoding(v_2823X);
    v_2825X = STDERR_FD();
    error_encoding_2826X = ps_console_encoding(v_2825X);
    if ((NULL == input_encoding_2824X)) {
      goto L29211;}
    else {
      if ((NULL == output_encoding_2822X)) {
        goto L29211;}
      else {
        if ((NULL == error_encoding_2826X)) {
          goto L29211;}
        else {
          goto L29216;}}}}}
 L29211: {
  ps_error("out of memory, unable to continue", 0);
  goto L29216;}
 L29216: {
s48_make_availableAgc((PS_SHIFT_LEFT_INLINE((3 * (12 + ((((PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_LEFT_INLINE((strlen((char *) "standard output")), 2))), 3)) + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_LEFT_INLINE((strlen((char *) input_encoding_2824X)), 2))), 3))) + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_LEFT_INLINE((strlen((char *) output_encoding_2822X)), 2))), 3))) + (PS_SHIFT_RIGHT_INLINE((7 + (PS_SHIFT_LEFT_INLINE((strlen((char *) error_encoding_2826X)), 2))), 3))))), 3)));
  channel_2827X = STDERR_FD();
  merged_arg5K0 = "standard error";
  merged_arg0K1 = 0;
#ifdef USE_DIRECT_THREADING
  enter_string_return_address = &&enter_string_return_0;
#else
  enter_string_return_tag = 0;
#endif
  goto enter_string;
 enter_string_return_0:
  v_2828X = enter_string0_return_value;
  vm_channel_2829X = make_channel(8, v_2828X, (PS_SHIFT_LEFT_INLINE(channel_2827X, 2)), 1, 1, 1, 1, 0);
  *((Svm_channelsS) + channel_2827X) = vm_channel_2829X;
  channel_2830X = STDIN_FD();
  merged_arg5K0 = "standard input";
  merged_arg0K1 = 0;
#ifdef USE_DIRECT_THREADING
  enter_string_return_address = &&enter_string_return_1;
#else
  enter_string_return_tag = 1;
#endif
  goto enter_string;
 enter_string_return_1:
  v_2831X = enter_string0_return_value;
  vm_channel_2832X = make_channel(4, v_2831X, (PS_SHIFT_LEFT_INLINE(channel_2830X, 2)), 1, 1, 1, 1, 0);
  *((Svm_channelsS) + channel_2830X) = vm_channel_2832X;
  channel_2833X = STDOUT_FD();
  merged_arg5K0 = "standard output";
  merged_arg0K1 = 0;
#ifdef USE_DIRECT_THREADING
  enter_string_return_address = &&enter_string_return_2;
#else
  enter_string_return_tag = 2;
#endif
  goto enter_string;
 enter_string_return_2:
  v_2834X = enter_string0_return_value;
  vm_channel_2835X = make_channel(8, v_2834X, (PS_SHIFT_LEFT_INLINE(channel_2833X, 2)), 1, 1, 1, 1, 0);
  *((Svm_channelsS) + channel_2833X) = vm_channel_2835X;
  merged_arg5K0 = input_encoding_2824X;
  merged_arg0K1 = 0;
#ifdef USE_DIRECT_THREADING
  enter_string_return_address = &&enter_string_return_3;
#else
  enter_string_return_tag = 3;
#endif
  goto enter_string;
 enter_string_return_3:
  input_encoding_2836X = enter_string0_return_value;
  merged_arg5K0 = output_encoding_2822X;
  merged_arg0K1 = 0;
#ifdef USE_DIRECT_THREADING
  enter_string_return_address = &&enter_string_return_4;
#else
  enter_string_return_tag = 4;
#endif
  goto enter_string;
 enter_string_return_4:
  output_encoding_2837X = enter_string0_return_value;
  merged_arg5K0 = error_encoding_2826X;
  merged_arg0K1 = 0;
#ifdef USE_DIRECT_THREADING
  enter_string_return_address = &&enter_string_return_5;
#else
  enter_string_return_tag = 5;
#endif
  goto enter_string;
 enter_string_return_5:
  error_encoding_2838X = enter_string0_return_value;
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (vm_channel_2832X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (input_encoding_2836X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (vm_channel_2835X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (output_encoding_2837X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (vm_channel_2829X);
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (error_encoding_2838X);
  x_2839X = s48_resumer_records();
  SstackS = ((SstackS) + -8);
  *((long *) (SstackS)) = (long) (x_2839X);s48_initialization_completeB();
  v_2840X = s48_startup_procedure();
  return s48_restart(v_2840X, 8);}
 enter_string: {
  string_2792X = merged_arg5K0;{
  len_2841X = strlen((char *) string_2792X);
  len_2842X = PS_SHIFT_LEFT_INLINE(len_2841X, 2);
  addr_2843X = s48_allocate_small((8 + len_2842X));
  *((long *) addr_2843X) = (long) ((66 + (PS_SHIFT_LEFT_INLINE(len_2842X, 8))));
  s_2844X = 3 + (((long) (addr_2843X + 8)));
  arg0K0 = 0;
  goto L22308;}
 L22308: {
  i_2845X = arg0K0;
  if ((i_2845X < len_2841X)) {
    c_2846X = ((unsigned char) (*(string_2792X + i_2845X)));
    arg0K0 = 0;
    arg0K1 = 0;
    arg0K2 = c_2846X;
    goto L22319;}
  else {
    enter_string0_return_value = s_2844X;
#ifdef USE_DIRECT_THREADING
    goto *enter_string_return_address;
#else
    goto enter_string_return;
#endif
}}
 L22319: {
  bits_2847X = arg0K0;
  j_2848X = arg0K1;
  shifted_2849X = arg0K2;
  if ((j_2848X < 4)) {
    *((unsigned char *) ((((char *) (-3 + s_2844X))) + ((PS_SHIFT_LEFT_INLINE(i_2845X, 2)) + j_2848X))) = (unsigned char) ((255 & shifted_2849X));
    arg0K0 = (8 + bits_2847X);
    arg0K1 = (1 + j_2848X);
    arg0K2 = (PS_SHIFT_RIGHT_LOGICAL_INLINE(shifted_2849X, 8));
    goto L22319;}
  else {
    arg0K0 = (1 + i_2845X);
    goto L22308;}}
#ifndef USE_DIRECT_THREADING
 enter_string_return:
  switch (enter_string_return_tag) {
  case 0: goto enter_string_return_0;
  case 1: goto enter_string_return_1;
  case 2: goto enter_string_return_2;
  case 3: goto enter_string_return_3;
  case 4: goto enter_string_return_4;
  default: goto enter_string_return_5;
  }
#endif
}

}void
s48_init(void)
{
Snumber_of_channelsS = 100;
Spending_channels_headS = 1;
Spending_channels_tailS = 1;
Sutf_8_state_tableS = malloc(128 * sizeof(long));
Sutf_8_state_tableS[0] = 0;
Sutf_8_state_tableS[1] = 0;
Sutf_8_state_tableS[2] = 0;
Sutf_8_state_tableS[3] = 0;
Sutf_8_state_tableS[4] = 0;
Sutf_8_state_tableS[5] = 0;
Sutf_8_state_tableS[6] = 0;
Sutf_8_state_tableS[7] = 0;
Sutf_8_state_tableS[8] = 0;
Sutf_8_state_tableS[9] = 0;
Sutf_8_state_tableS[10] = 0;
Sutf_8_state_tableS[11] = 0;
Sutf_8_state_tableS[12] = 0;
Sutf_8_state_tableS[13] = 0;
Sutf_8_state_tableS[14] = 0;
Sutf_8_state_tableS[15] = 0;
Sutf_8_state_tableS[16] = -1;
Sutf_8_state_tableS[17] = -1;
Sutf_8_state_tableS[18] = -1;
Sutf_8_state_tableS[19] = -1;
Sutf_8_state_tableS[20] = -1;
Sutf_8_state_tableS[21] = -1;
Sutf_8_state_tableS[22] = -1;
Sutf_8_state_tableS[23] = -1;
Sutf_8_state_tableS[24] = 1;
Sutf_8_state_tableS[25] = 1;
Sutf_8_state_tableS[26] = 1;
Sutf_8_state_tableS[27] = 1;
Sutf_8_state_tableS[28] = 2;
Sutf_8_state_tableS[29] = 2;
Sutf_8_state_tableS[30] = 3;
Sutf_8_state_tableS[31] = -1;
Sutf_8_state_tableS[32] = -2;
Sutf_8_state_tableS[33] = -2;
Sutf_8_state_tableS[34] = -2;
Sutf_8_state_tableS[35] = -2;
Sutf_8_state_tableS[36] = -2;
Sutf_8_state_tableS[37] = -2;
Sutf_8_state_tableS[38] = -2;
Sutf_8_state_tableS[39] = -2;
Sutf_8_state_tableS[40] = -2;
Sutf_8_state_tableS[41] = -2;
Sutf_8_state_tableS[42] = -2;
Sutf_8_state_tableS[43] = -2;
Sutf_8_state_tableS[44] = -2;
Sutf_8_state_tableS[45] = -2;
Sutf_8_state_tableS[46] = -2;
Sutf_8_state_tableS[47] = -2;
Sutf_8_state_tableS[48] = 0;
Sutf_8_state_tableS[49] = 0;
Sutf_8_state_tableS[50] = 0;
Sutf_8_state_tableS[51] = 0;
Sutf_8_state_tableS[52] = 0;
Sutf_8_state_tableS[53] = 0;
Sutf_8_state_tableS[54] = 0;
Sutf_8_state_tableS[55] = 0;
Sutf_8_state_tableS[56] = -2;
Sutf_8_state_tableS[57] = -2;
Sutf_8_state_tableS[58] = -2;
Sutf_8_state_tableS[59] = -2;
Sutf_8_state_tableS[60] = -2;
Sutf_8_state_tableS[61] = -2;
Sutf_8_state_tableS[62] = -2;
Sutf_8_state_tableS[63] = -2;
Sutf_8_state_tableS[64] = -2;
Sutf_8_state_tableS[65] = -2;
Sutf_8_state_tableS[66] = -2;
Sutf_8_state_tableS[67] = -2;
Sutf_8_state_tableS[68] = -2;
Sutf_8_state_tableS[69] = -2;
Sutf_8_state_tableS[70] = -2;
Sutf_8_state_tableS[71] = -2;
Sutf_8_state_tableS[72] = -2;
Sutf_8_state_tableS[73] = -2;
Sutf_8_state_tableS[74] = -2;
Sutf_8_state_tableS[75] = -2;
Sutf_8_state_tableS[76] = -2;
Sutf_8_state_tableS[77] = -2;
Sutf_8_state_tableS[78] = -2;
Sutf_8_state_tableS[79] = -2;
Sutf_8_state_tableS[80] = 1;
Sutf_8_state_tableS[81] = 1;
Sutf_8_state_tableS[82] = 1;
Sutf_8_state_tableS[83] = 1;
Sutf_8_state_tableS[84] = 1;
Sutf_8_state_tableS[85] = 1;
Sutf_8_state_tableS[86] = 1;
Sutf_8_state_tableS[87] = 1;
Sutf_8_state_tableS[88] = -2;
Sutf_8_state_tableS[89] = -2;
Sutf_8_state_tableS[90] = -2;
Sutf_8_state_tableS[91] = -2;
Sutf_8_state_tableS[92] = -2;
Sutf_8_state_tableS[93] = -2;
Sutf_8_state_tableS[94] = -2;
Sutf_8_state_tableS[95] = -2;
Sutf_8_state_tableS[96] = -2;
Sutf_8_state_tableS[97] = -2;
Sutf_8_state_tableS[98] = -2;
Sutf_8_state_tableS[99] = -2;
Sutf_8_state_tableS[100] = -2;
Sutf_8_state_tableS[101] = -2;
Sutf_8_state_tableS[102] = -2;
Sutf_8_state_tableS[103] = -2;
Sutf_8_state_tableS[104] = -2;
Sutf_8_state_tableS[105] = -2;
Sutf_8_state_tableS[106] = -2;
Sutf_8_state_tableS[107] = -2;
Sutf_8_state_tableS[108] = -2;
Sutf_8_state_tableS[109] = -2;
Sutf_8_state_tableS[110] = -2;
Sutf_8_state_tableS[111] = -2;
Sutf_8_state_tableS[112] = 2;
Sutf_8_state_tableS[113] = 2;
Sutf_8_state_tableS[114] = 2;
Sutf_8_state_tableS[115] = 2;
Sutf_8_state_tableS[116] = 2;
Sutf_8_state_tableS[117] = 2;
Sutf_8_state_tableS[118] = 2;
Sutf_8_state_tableS[119] = 2;
Sutf_8_state_tableS[120] = -2;
Sutf_8_state_tableS[121] = -2;
Sutf_8_state_tableS[122] = -2;
Sutf_8_state_tableS[123] = -2;
Sutf_8_state_tableS[124] = -2;
Sutf_8_state_tableS[125] = -2;
Sutf_8_state_tableS[126] = -2;
Sutf_8_state_tableS[127] = -2;
Sutf_8_masksS = malloc(4 * sizeof(long));
Sutf_8_masksS[0] = 127;
Sutf_8_masksS[1] = 31;
Sutf_8_masksS[2] = 15;
Sutf_8_masksS[3] = 7;
Stemp0S = 1;
Stemp1S = 1;
Sstack_warningPS = 1;
Simported_bindingsS = 1;
Sexported_bindingsS = 1;
Snumber_of_event_typesS = 100;
Sgc_in_troublePS = 0;
Sos_signal_ringS = malloc(32 * sizeof(long));
Sos_signal_ringS[0] = 0;
Sos_signal_ringS[1] = 0;
Sos_signal_ringS[2] = 0;
Sos_signal_ringS[3] = 0;
Sos_signal_ringS[4] = 0;
Sos_signal_ringS[5] = 0;
Sos_signal_ringS[6] = 0;
Sos_signal_ringS[7] = 0;
Sos_signal_ringS[8] = 0;
Sos_signal_ringS[9] = 0;
Sos_signal_ringS[10] = 0;
Sos_signal_ringS[11] = 0;
Sos_signal_ringS[12] = 0;
Sos_signal_ringS[13] = 0;
Sos_signal_ringS[14] = 0;
Sos_signal_ringS[15] = 0;
Sos_signal_ringS[16] = 0;
Sos_signal_ringS[17] = 0;
Sos_signal_ringS[18] = 0;
Sos_signal_ringS[19] = 0;
Sos_signal_ringS[20] = 0;
Sos_signal_ringS[21] = 0;
Sos_signal_ringS[22] = 0;
Sos_signal_ringS[23] = 0;
Sos_signal_ringS[24] = 0;
Sos_signal_ringS[25] = 0;
Sos_signal_ringS[26] = 0;
Sos_signal_ringS[27] = 0;
Sos_signal_ringS[28] = 0;
Sos_signal_ringS[29] = 0;
Sos_signal_ringS[30] = 0;
Sos_signal_ringS[31] = 0;
Sos_signal_ring_startS = 0;
Sos_signal_ring_readyS = 0;
Sos_signal_ring_endS = 0;
Sexternal_exceptionPS = 0;
Sexternal_root_stackS = NULL;
Sexternal_root_stack_baseS = NULL;
Spermanent_external_rootsS = NULL;
Spost_gc_cleanupS = HtopD12305;
Sgc_root_procS = HtopD12316;
Snative_exception_contS = 0;
s48_Scallback_return_stack_blockS = 1;
s48_Spending_eventsPS = 0;
}
