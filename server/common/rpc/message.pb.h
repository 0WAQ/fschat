// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: message.proto
// Protobuf C++ Version: 6.30.0

#ifndef message_2eproto_2epb_2eh
#define message_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/runtime_version.h"
#if PROTOBUF_VERSION != 6030000
#error "Protobuf C++ gencode is built with an incompatible version of"
#error "Protobuf C++ headers/runtime. See"
#error "https://protobuf.dev/support/cross-version-runtime-guarantee/#cpp"
#endif
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/message_lite.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_message_2eproto

namespace google {
namespace protobuf {
namespace internal {
template <typename T>
::absl::string_view GetAnyMessageName();
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_message_2eproto {
  static const ::uint32_t offsets[];
};
extern "C" {
extern const ::google::protobuf::internal::DescriptorTable descriptor_table_message_2eproto;
}  // extern "C"
namespace message {
class GetVerifyCodeReq;
struct GetVerifyCodeReqDefaultTypeInternal;
extern GetVerifyCodeReqDefaultTypeInternal _GetVerifyCodeReq_default_instance_;
extern const ::google::protobuf::internal::ClassDataFull GetVerifyCodeReq_class_data_;
class GetVerifyCodeRsp;
struct GetVerifyCodeRspDefaultTypeInternal;
extern GetVerifyCodeRspDefaultTypeInternal _GetVerifyCodeRsp_default_instance_;
extern const ::google::protobuf::internal::ClassDataFull GetVerifyCodeRsp_class_data_;
}  // namespace message
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace message {

// ===================================================================


// -------------------------------------------------------------------

class GetVerifyCodeRsp final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:message.GetVerifyCodeRsp) */ {
 public:
  inline GetVerifyCodeRsp() : GetVerifyCodeRsp(nullptr) {}
  ~GetVerifyCodeRsp() PROTOBUF_FINAL;

#if defined(PROTOBUF_CUSTOM_VTABLE)
  void operator delete(GetVerifyCodeRsp* PROTOBUF_NONNULL msg, std::destroying_delete_t) {
    SharedDtor(*msg);
    ::google::protobuf::internal::SizedDelete(msg, sizeof(GetVerifyCodeRsp));
  }
#endif

  template <typename = void>
  explicit PROTOBUF_CONSTEXPR GetVerifyCodeRsp(::google::protobuf::internal::ConstantInitialized);

  inline GetVerifyCodeRsp(const GetVerifyCodeRsp& from) : GetVerifyCodeRsp(nullptr, from) {}
  inline GetVerifyCodeRsp(GetVerifyCodeRsp&& from) noexcept
      : GetVerifyCodeRsp(nullptr, std::move(from)) {}
  inline GetVerifyCodeRsp& operator=(const GetVerifyCodeRsp& from) {
    CopyFrom(from);
    return *this;
  }
  inline GetVerifyCodeRsp& operator=(GetVerifyCodeRsp&& from) noexcept {
    if (this == &from) return *this;
    if (::google::protobuf::internal::CanMoveWithInternalSwap(GetArena(), from.GetArena())) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* PROTOBUF_NONNULL mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* PROTOBUF_NONNULL descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* PROTOBUF_NONNULL GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* PROTOBUF_NONNULL GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const GetVerifyCodeRsp& default_instance() {
    return *reinterpret_cast<const GetVerifyCodeRsp*>(
        &_GetVerifyCodeRsp_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 1;
  friend void swap(GetVerifyCodeRsp& a, GetVerifyCodeRsp& b) { a.Swap(&b); }
  inline void Swap(GetVerifyCodeRsp* PROTOBUF_NONNULL other) {
    if (other == this) return;
    if (::google::protobuf::internal::CanUseInternalSwap(GetArena(), other->GetArena())) {
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(GetVerifyCodeRsp* PROTOBUF_NONNULL other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  GetVerifyCodeRsp* PROTOBUF_NONNULL New(::google::protobuf::Arena* PROTOBUF_NULLABLE arena = nullptr) const {
    return ::google::protobuf::Message::DefaultConstruct<GetVerifyCodeRsp>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const GetVerifyCodeRsp& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const GetVerifyCodeRsp& from) { GetVerifyCodeRsp::MergeImpl(*this, from); }

  private:
  static void MergeImpl(::google::protobuf::MessageLite& to_msg,
                        const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() PROTOBUF_FINAL;
  #if defined(PROTOBUF_CUSTOM_VTABLE)
  private:
  static ::size_t ByteSizeLong(const ::google::protobuf::MessageLite& msg);
  static ::uint8_t* PROTOBUF_NONNULL _InternalSerialize(
      const ::google::protobuf::MessageLite& msg, ::uint8_t* PROTOBUF_NONNULL target,
      ::google::protobuf::io::EpsCopyOutputStream* PROTOBUF_NONNULL stream);

  public:
  ::size_t ByteSizeLong() const { return ByteSizeLong(*this); }
  ::uint8_t* PROTOBUF_NONNULL _InternalSerialize(
      ::uint8_t* PROTOBUF_NONNULL target,
      ::google::protobuf::io::EpsCopyOutputStream* PROTOBUF_NONNULL stream) const {
    return _InternalSerialize(*this, target, stream);
  }
  #else   // PROTOBUF_CUSTOM_VTABLE
  ::size_t ByteSizeLong() const final;
  ::uint8_t* PROTOBUF_NONNULL _InternalSerialize(
      ::uint8_t* PROTOBUF_NONNULL target,
      ::google::protobuf::io::EpsCopyOutputStream* PROTOBUF_NONNULL stream) const final;
  #endif  // PROTOBUF_CUSTOM_VTABLE
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* PROTOBUF_NULLABLE arena);
  static void SharedDtor(MessageLite& self);
  void InternalSwap(GetVerifyCodeRsp* PROTOBUF_NONNULL other);
 private:
  template <typename T>
  friend ::absl::string_view(::google::protobuf::internal::GetAnyMessageName)();
  static ::absl::string_view FullMessageName() { return "message.GetVerifyCodeRsp"; }

 protected:
  explicit GetVerifyCodeRsp(::google::protobuf::Arena* PROTOBUF_NULLABLE arena);
  GetVerifyCodeRsp(::google::protobuf::Arena* PROTOBUF_NULLABLE arena, const GetVerifyCodeRsp& from);
  GetVerifyCodeRsp(
      ::google::protobuf::Arena* PROTOBUF_NULLABLE arena, GetVerifyCodeRsp&& from) noexcept
      : GetVerifyCodeRsp(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::internal::ClassData* PROTOBUF_NONNULL GetClassData() const PROTOBUF_FINAL;
  static void* PROTOBUF_NONNULL PlacementNew_(
      const void* PROTOBUF_NONNULL, void* PROTOBUF_NONNULL mem,
      ::google::protobuf::Arena* PROTOBUF_NULLABLE arena);
  static constexpr auto InternalNewImpl_();

 public:
  static constexpr auto InternalGenerateClassData_();

  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kEmailFieldNumber = 2,
    kCodeFieldNumber = 3,
    kErrorFieldNumber = 1,
  };
  // string email = 2;
  void clear_email() ;
  const std::string& email() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_email(Arg_&& arg, Args_... args);
  std::string* PROTOBUF_NONNULL mutable_email();
  [[nodiscard]] std::string* PROTOBUF_NULLABLE release_email();
  void set_allocated_email(std::string* PROTOBUF_NULLABLE value);

  private:
  const std::string& _internal_email() const;
  PROTOBUF_ALWAYS_INLINE void _internal_set_email(const std::string& value);
  std::string* PROTOBUF_NONNULL _internal_mutable_email();

  public:
  // string code = 3;
  void clear_code() ;
  const std::string& code() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_code(Arg_&& arg, Args_... args);
  std::string* PROTOBUF_NONNULL mutable_code();
  [[nodiscard]] std::string* PROTOBUF_NULLABLE release_code();
  void set_allocated_code(std::string* PROTOBUF_NULLABLE value);

  private:
  const std::string& _internal_code() const;
  PROTOBUF_ALWAYS_INLINE void _internal_set_code(const std::string& value);
  std::string* PROTOBUF_NONNULL _internal_mutable_code();

  public:
  // int32 error = 1;
  void clear_error() ;
  ::int32_t error() const;
  void set_error(::int32_t value);

  private:
  ::int32_t _internal_error() const;
  void _internal_set_error(::int32_t value);

  public:
  // @@protoc_insertion_point(class_scope:message.GetVerifyCodeRsp)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<2, 3,
                                   0, 42,
                                   2>
      _table_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(
        ::google::protobuf::internal::InternalVisibility visibility,
        ::google::protobuf::Arena* PROTOBUF_NULLABLE arena);
    inline explicit Impl_(
        ::google::protobuf::internal::InternalVisibility visibility,
        ::google::protobuf::Arena* PROTOBUF_NULLABLE arena, const Impl_& from,
        const GetVerifyCodeRsp& from_msg);
    ::google::protobuf::internal::HasBits<1> _has_bits_;
    ::google::protobuf::internal::CachedSize _cached_size_;
    ::google::protobuf::internal::ArenaStringPtr email_;
    ::google::protobuf::internal::ArenaStringPtr code_;
    ::int32_t error_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_message_2eproto;
};

extern const ::google::protobuf::internal::ClassDataFull GetVerifyCodeRsp_class_data_;
// -------------------------------------------------------------------

class GetVerifyCodeReq final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:message.GetVerifyCodeReq) */ {
 public:
  inline GetVerifyCodeReq() : GetVerifyCodeReq(nullptr) {}
  ~GetVerifyCodeReq() PROTOBUF_FINAL;

#if defined(PROTOBUF_CUSTOM_VTABLE)
  void operator delete(GetVerifyCodeReq* PROTOBUF_NONNULL msg, std::destroying_delete_t) {
    SharedDtor(*msg);
    ::google::protobuf::internal::SizedDelete(msg, sizeof(GetVerifyCodeReq));
  }
#endif

  template <typename = void>
  explicit PROTOBUF_CONSTEXPR GetVerifyCodeReq(::google::protobuf::internal::ConstantInitialized);

  inline GetVerifyCodeReq(const GetVerifyCodeReq& from) : GetVerifyCodeReq(nullptr, from) {}
  inline GetVerifyCodeReq(GetVerifyCodeReq&& from) noexcept
      : GetVerifyCodeReq(nullptr, std::move(from)) {}
  inline GetVerifyCodeReq& operator=(const GetVerifyCodeReq& from) {
    CopyFrom(from);
    return *this;
  }
  inline GetVerifyCodeReq& operator=(GetVerifyCodeReq&& from) noexcept {
    if (this == &from) return *this;
    if (::google::protobuf::internal::CanMoveWithInternalSwap(GetArena(), from.GetArena())) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* PROTOBUF_NONNULL mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* PROTOBUF_NONNULL descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* PROTOBUF_NONNULL GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* PROTOBUF_NONNULL GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const GetVerifyCodeReq& default_instance() {
    return *reinterpret_cast<const GetVerifyCodeReq*>(
        &_GetVerifyCodeReq_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(GetVerifyCodeReq& a, GetVerifyCodeReq& b) { a.Swap(&b); }
  inline void Swap(GetVerifyCodeReq* PROTOBUF_NONNULL other) {
    if (other == this) return;
    if (::google::protobuf::internal::CanUseInternalSwap(GetArena(), other->GetArena())) {
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(GetVerifyCodeReq* PROTOBUF_NONNULL other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  GetVerifyCodeReq* PROTOBUF_NONNULL New(::google::protobuf::Arena* PROTOBUF_NULLABLE arena = nullptr) const {
    return ::google::protobuf::Message::DefaultConstruct<GetVerifyCodeReq>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const GetVerifyCodeReq& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const GetVerifyCodeReq& from) { GetVerifyCodeReq::MergeImpl(*this, from); }

  private:
  static void MergeImpl(::google::protobuf::MessageLite& to_msg,
                        const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() PROTOBUF_FINAL;
  #if defined(PROTOBUF_CUSTOM_VTABLE)
  private:
  static ::size_t ByteSizeLong(const ::google::protobuf::MessageLite& msg);
  static ::uint8_t* PROTOBUF_NONNULL _InternalSerialize(
      const ::google::protobuf::MessageLite& msg, ::uint8_t* PROTOBUF_NONNULL target,
      ::google::protobuf::io::EpsCopyOutputStream* PROTOBUF_NONNULL stream);

  public:
  ::size_t ByteSizeLong() const { return ByteSizeLong(*this); }
  ::uint8_t* PROTOBUF_NONNULL _InternalSerialize(
      ::uint8_t* PROTOBUF_NONNULL target,
      ::google::protobuf::io::EpsCopyOutputStream* PROTOBUF_NONNULL stream) const {
    return _InternalSerialize(*this, target, stream);
  }
  #else   // PROTOBUF_CUSTOM_VTABLE
  ::size_t ByteSizeLong() const final;
  ::uint8_t* PROTOBUF_NONNULL _InternalSerialize(
      ::uint8_t* PROTOBUF_NONNULL target,
      ::google::protobuf::io::EpsCopyOutputStream* PROTOBUF_NONNULL stream) const final;
  #endif  // PROTOBUF_CUSTOM_VTABLE
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* PROTOBUF_NULLABLE arena);
  static void SharedDtor(MessageLite& self);
  void InternalSwap(GetVerifyCodeReq* PROTOBUF_NONNULL other);
 private:
  template <typename T>
  friend ::absl::string_view(::google::protobuf::internal::GetAnyMessageName)();
  static ::absl::string_view FullMessageName() { return "message.GetVerifyCodeReq"; }

 protected:
  explicit GetVerifyCodeReq(::google::protobuf::Arena* PROTOBUF_NULLABLE arena);
  GetVerifyCodeReq(::google::protobuf::Arena* PROTOBUF_NULLABLE arena, const GetVerifyCodeReq& from);
  GetVerifyCodeReq(
      ::google::protobuf::Arena* PROTOBUF_NULLABLE arena, GetVerifyCodeReq&& from) noexcept
      : GetVerifyCodeReq(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::internal::ClassData* PROTOBUF_NONNULL GetClassData() const PROTOBUF_FINAL;
  static void* PROTOBUF_NONNULL PlacementNew_(
      const void* PROTOBUF_NONNULL, void* PROTOBUF_NONNULL mem,
      ::google::protobuf::Arena* PROTOBUF_NULLABLE arena);
  static constexpr auto InternalNewImpl_();

 public:
  static constexpr auto InternalGenerateClassData_();

  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kEmailFieldNumber = 1,
  };
  // string email = 1;
  void clear_email() ;
  const std::string& email() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_email(Arg_&& arg, Args_... args);
  std::string* PROTOBUF_NONNULL mutable_email();
  [[nodiscard]] std::string* PROTOBUF_NULLABLE release_email();
  void set_allocated_email(std::string* PROTOBUF_NULLABLE value);

  private:
  const std::string& _internal_email() const;
  PROTOBUF_ALWAYS_INLINE void _internal_set_email(const std::string& value);
  std::string* PROTOBUF_NONNULL _internal_mutable_email();

  public:
  // @@protoc_insertion_point(class_scope:message.GetVerifyCodeReq)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<0, 1,
                                   0, 38,
                                   2>
      _table_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(
        ::google::protobuf::internal::InternalVisibility visibility,
        ::google::protobuf::Arena* PROTOBUF_NULLABLE arena);
    inline explicit Impl_(
        ::google::protobuf::internal::InternalVisibility visibility,
        ::google::protobuf::Arena* PROTOBUF_NULLABLE arena, const Impl_& from,
        const GetVerifyCodeReq& from_msg);
    ::google::protobuf::internal::HasBits<1> _has_bits_;
    ::google::protobuf::internal::CachedSize _cached_size_;
    ::google::protobuf::internal::ArenaStringPtr email_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_message_2eproto;
};

extern const ::google::protobuf::internal::ClassDataFull GetVerifyCodeReq_class_data_;

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// GetVerifyCodeReq

// string email = 1;
inline void GetVerifyCodeReq::clear_email() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.email_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline const std::string& GetVerifyCodeReq::email() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:message.GetVerifyCodeReq.email)
  return _internal_email();
}
template <typename Arg_, typename... Args_>
PROTOBUF_ALWAYS_INLINE void GetVerifyCodeReq::set_email(Arg_&& arg, Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.email_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:message.GetVerifyCodeReq.email)
}
inline std::string* PROTOBUF_NONNULL GetVerifyCodeReq::mutable_email()
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_email();
  // @@protoc_insertion_point(field_mutable:message.GetVerifyCodeReq.email)
  return _s;
}
inline const std::string& GetVerifyCodeReq::_internal_email() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.email_.Get();
}
inline void GetVerifyCodeReq::_internal_set_email(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.email_.Set(value, GetArena());
}
inline std::string* PROTOBUF_NONNULL GetVerifyCodeReq::_internal_mutable_email() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_._has_bits_[0] |= 0x00000001u;
  return _impl_.email_.Mutable( GetArena());
}
inline std::string* PROTOBUF_NULLABLE GetVerifyCodeReq::release_email() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:message.GetVerifyCodeReq.email)
  if ((_impl_._has_bits_[0] & 0x00000001u) == 0) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000001u;
  auto* released = _impl_.email_.Release();
  if (::google::protobuf::internal::DebugHardenForceCopyDefaultString()) {
    _impl_.email_.Set("", GetArena());
  }
  return released;
}
inline void GetVerifyCodeReq::set_allocated_email(std::string* PROTOBUF_NULLABLE value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }
  _impl_.email_.SetAllocated(value, GetArena());
  if (::google::protobuf::internal::DebugHardenForceCopyDefaultString() && _impl_.email_.IsDefault()) {
    _impl_.email_.Set("", GetArena());
  }
  // @@protoc_insertion_point(field_set_allocated:message.GetVerifyCodeReq.email)
}

// -------------------------------------------------------------------

// GetVerifyCodeRsp

// int32 error = 1;
inline void GetVerifyCodeRsp::clear_error() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.error_ = 0;
  _impl_._has_bits_[0] &= ~0x00000004u;
}
inline ::int32_t GetVerifyCodeRsp::error() const {
  // @@protoc_insertion_point(field_get:message.GetVerifyCodeRsp.error)
  return _internal_error();
}
inline void GetVerifyCodeRsp::set_error(::int32_t value) {
  _internal_set_error(value);
  _impl_._has_bits_[0] |= 0x00000004u;
  // @@protoc_insertion_point(field_set:message.GetVerifyCodeRsp.error)
}
inline ::int32_t GetVerifyCodeRsp::_internal_error() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.error_;
}
inline void GetVerifyCodeRsp::_internal_set_error(::int32_t value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.error_ = value;
}

// string email = 2;
inline void GetVerifyCodeRsp::clear_email() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.email_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline const std::string& GetVerifyCodeRsp::email() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:message.GetVerifyCodeRsp.email)
  return _internal_email();
}
template <typename Arg_, typename... Args_>
PROTOBUF_ALWAYS_INLINE void GetVerifyCodeRsp::set_email(Arg_&& arg, Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.email_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:message.GetVerifyCodeRsp.email)
}
inline std::string* PROTOBUF_NONNULL GetVerifyCodeRsp::mutable_email()
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_email();
  // @@protoc_insertion_point(field_mutable:message.GetVerifyCodeRsp.email)
  return _s;
}
inline const std::string& GetVerifyCodeRsp::_internal_email() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.email_.Get();
}
inline void GetVerifyCodeRsp::_internal_set_email(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.email_.Set(value, GetArena());
}
inline std::string* PROTOBUF_NONNULL GetVerifyCodeRsp::_internal_mutable_email() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_._has_bits_[0] |= 0x00000001u;
  return _impl_.email_.Mutable( GetArena());
}
inline std::string* PROTOBUF_NULLABLE GetVerifyCodeRsp::release_email() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:message.GetVerifyCodeRsp.email)
  if ((_impl_._has_bits_[0] & 0x00000001u) == 0) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000001u;
  auto* released = _impl_.email_.Release();
  if (::google::protobuf::internal::DebugHardenForceCopyDefaultString()) {
    _impl_.email_.Set("", GetArena());
  }
  return released;
}
inline void GetVerifyCodeRsp::set_allocated_email(std::string* PROTOBUF_NULLABLE value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }
  _impl_.email_.SetAllocated(value, GetArena());
  if (::google::protobuf::internal::DebugHardenForceCopyDefaultString() && _impl_.email_.IsDefault()) {
    _impl_.email_.Set("", GetArena());
  }
  // @@protoc_insertion_point(field_set_allocated:message.GetVerifyCodeRsp.email)
}

// string code = 3;
inline void GetVerifyCodeRsp::clear_code() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.code_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000002u;
}
inline const std::string& GetVerifyCodeRsp::code() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:message.GetVerifyCodeRsp.code)
  return _internal_code();
}
template <typename Arg_, typename... Args_>
PROTOBUF_ALWAYS_INLINE void GetVerifyCodeRsp::set_code(Arg_&& arg, Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_._has_bits_[0] |= 0x00000002u;
  _impl_.code_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:message.GetVerifyCodeRsp.code)
}
inline std::string* PROTOBUF_NONNULL GetVerifyCodeRsp::mutable_code()
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_code();
  // @@protoc_insertion_point(field_mutable:message.GetVerifyCodeRsp.code)
  return _s;
}
inline const std::string& GetVerifyCodeRsp::_internal_code() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.code_.Get();
}
inline void GetVerifyCodeRsp::_internal_set_code(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_._has_bits_[0] |= 0x00000002u;
  _impl_.code_.Set(value, GetArena());
}
inline std::string* PROTOBUF_NONNULL GetVerifyCodeRsp::_internal_mutable_code() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_._has_bits_[0] |= 0x00000002u;
  return _impl_.code_.Mutable( GetArena());
}
inline std::string* PROTOBUF_NULLABLE GetVerifyCodeRsp::release_code() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:message.GetVerifyCodeRsp.code)
  if ((_impl_._has_bits_[0] & 0x00000002u) == 0) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000002u;
  auto* released = _impl_.code_.Release();
  if (::google::protobuf::internal::DebugHardenForceCopyDefaultString()) {
    _impl_.code_.Set("", GetArena());
  }
  return released;
}
inline void GetVerifyCodeRsp::set_allocated_code(std::string* PROTOBUF_NULLABLE value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000002u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000002u;
  }
  _impl_.code_.SetAllocated(value, GetArena());
  if (::google::protobuf::internal::DebugHardenForceCopyDefaultString() && _impl_.code_.IsDefault()) {
    _impl_.code_.Set("", GetArena());
  }
  // @@protoc_insertion_point(field_set_allocated:message.GetVerifyCodeRsp.code)
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace message


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // message_2eproto_2epb_2eh
