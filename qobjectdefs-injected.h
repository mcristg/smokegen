static const char Injected[] = R"-(
#ifndef Q_MOC_OUTPUT_REVISION
#define Q_MOC_OUTPUT_REVISION 68
#endif

// The following macros can be defined by tools that understand Qt
// to have the information from the macro.
#ifndef QT_ANNOTATE_CLASS
# define QT_ANNOTATE_CLASS(type, ...)
#endif
#ifndef QT_ANNOTATE_CLASS2
# define QT_ANNOTATE_CLASS2(type, a1, a2)
#endif
#ifndef QT_ANNOTATE_FUNCTION
# define QT_ANNOTATE_FUNCTION(x)
#endif
#ifndef QT_ANNOTATE_ACCESS_SPECIFIER
# define QT_ANNOTATE_ACCESS_SPECIFIER(x)
#endif

// The following macros are our "extensions" to C++
// They are used, strictly speaking, only by the moc.

#ifndef Q_MOC_RUN
#ifndef QT_NO_META_MACROS
# if defined(QT_NO_KEYWORDS)
#  define QT_NO_EMIT
# else
#   ifndef QT_NO_SIGNALS_SLOTS_KEYWORDS
#     define slots Q_SLOTS
#     define signals Q_SIGNALS
#   endif
# endif
# define Q_SLOTS QT_ANNOTATE_ACCESS_SPECIFIER(qt_slot)
# define Q_SIGNALS public QT_ANNOTATE_ACCESS_SPECIFIER(qt_signal)
# define Q_PRIVATE_SLOT(d, signature) QT_ANNOTATE_CLASS2(qt_private_slot, d, signature)
# define Q_EMIT
#ifndef QT_NO_EMIT
# define emit
#endif
#ifndef Q_CLASSINFO
# define Q_CLASSINFO(name, value)
#endif
#define Q_PLUGIN_METADATA(x) QT_ANNOTATE_CLASS(qt_plugin_metadata, x)
#define Q_INTERFACES(x) QT_ANNOTATE_CLASS(qt_interfaces, x)
#define Q_PROPERTY(...) QT_ANNOTATE_CLASS(qt_property, __VA_ARGS__)
#define Q_PRIVATE_PROPERTY(d, text) QT_ANNOTATE_CLASS2(qt_private_property, d, text)
#ifndef Q_REVISION
# define Q_REVISION(...)
#endif
#define Q_OVERRIDE(text) QT_ANNOTATE_CLASS(qt_override, text)
#define QDOC_PROPERTY(text) QT_ANNOTATE_CLASS(qt_qdoc_property, text)
#define Q_ENUMS(x) QT_ANNOTATE_CLASS(qt_enums, x)
#define Q_FLAGS(x) QT_ANNOTATE_CLASS(qt_enums, x)
#undef Q_ENUM_IMPL
#define Q_ENUM_IMPL(ENUM) \
    friend constexpr const QMetaObject *qt_getEnumMetaObject(ENUM) noexcept { return &staticMetaObject; } \
    friend constexpr const char *qt_getEnumName(ENUM) noexcept { return #ENUM; }
#define Q_ENUM(x) Q_ENUMS(x) Q_ENUM_IMPL(x)
#define Q_FLAG(x) Q_FLAGS(x) Q_ENUM_IMPL(x)
#undef Q_ENUM_NS_IMPL
#define Q_ENUM_NS_IMPL(ENUM) \
    inline constexpr const QMetaObject *qt_getEnumMetaObject(ENUM) noexcept { return &staticMetaObject; } \
    inline constexpr const char *qt_getEnumName(ENUM) noexcept { return #ENUM; }
#define Q_ENUM_NS(x) Q_ENUMS(x) Q_ENUM_NS_IMPL(x)
#define Q_FLAG_NS(x) Q_FLAGS(x) Q_ENUM_NS_IMPL(x)
#define Q_SCRIPTABLE QT_ANNOTATE_FUNCTION(qt_scriptable)
#define Q_INVOKABLE  QT_ANNOTATE_FUNCTION(qt_invokable)
#define Q_SIGNAL QT_ANNOTATE_FUNCTION(qt_signal)
#define Q_SLOT QT_ANNOTATE_FUNCTION(qt_slot)
#define Q_MOC_INCLUDE(...) QT_ANNOTATE_CLASS(qt_moc_include, __VA_ARGS__)
#endif // QT_NO_META_MACROS


/* qmake ignore Q_OBJECT */
#define Q_OBJECT \
public: \
    QT_WARNING_PUSH \
    Q_OBJECT_NO_OVERRIDE_WARNING \
    static const QMetaObject staticMetaObject; \
    virtual const QMetaObject *metaObject() const; \
    virtual void *qt_metacast(const char *); \
    virtual int qt_metacall(QMetaObject::Call, int, void **); \
    QT_TR_FUNCTIONS \
private: \
    Q_OBJECT_NO_ATTRIBUTES_WARNING \
    Q_DECL_HIDDEN_STATIC_METACALL static void qt_static_metacall(QObject *, QMetaObject::Call, int, void **); \
    QT_WARNING_POP \
    struct QPrivateSignal {}; \
    QT_ANNOTATE_CLASS(qt_qobject, "")

/* qmake ignore Q_OBJECT */
#define Q_OBJECT_FAKE Q_OBJECT QT_ANNOTATE_CLASS(qt_fake, "")

#ifndef QT_NO_META_MACROS
/* qmake ignore Q_GADGET */
#undef Q_GADGET
#define Q_GADGET \
public: \
    static const QMetaObject staticMetaObject; \
    typedef void QtGadgetHelper; \
private: \
    QT_WARNING_PUSH \
    Q_OBJECT_NO_ATTRIBUTES_WARNING \
    Q_DECL_HIDDEN_STATIC_METACALL static void qt_static_metacall(QObject *, QMetaObject::Call, int, void **); \
    QT_WARNING_POP \
    QT_ANNOTATE_CLASS(qt_qgadget, "") \
    /*end*/

/* qmake ignore Q_NAMESPACE_EXPORT */
#define Q_NAMESPACE_EXPORT(...) \
    extern __VA_ARGS__ const QMetaObject staticMetaObject; \
    QT_ANNOTATE_CLASS(qt_qnamespace, "") \
    /*end*/

/* qmake ignore Q_NAMESPACE */
#define Q_NAMESPACE Q_NAMESPACE_EXPORT() \
    /*end*/

#endif // QT_NO_META_MACROS

#else // Q_MOC_RUN
#define slots slots
#define signals signals
#define Q_SLOTS Q_SLOTS
#define Q_SIGNALS Q_SIGNALS
#define Q_CLASSINFO(name, value) Q_CLASSINFO(name, value)
#define Q_INTERFACES(x) Q_INTERFACES(x)
#define Q_PROPERTY(text) Q_PROPERTY(text)
#define Q_PRIVATE_PROPERTY(d, text) Q_PRIVATE_PROPERTY(d, text)
#define Q_PRIVATE_QPROPERTY(accessor, type, name, setter, ...) Q_PRIVATE_QPROPERTY(accessor, type, name, setter, __VA_ARGS__)
#define Q_PRIVATE_QPROPERTIES_BEGIN
#define Q_PRIVATE_QPROPERTY_IMPL(name)
#define Q_PRIVATE_QPROPERTIES_END
#define Q_REVISION(...) Q_REVISION(__VA_ARGS__)
#define Q_OVERRIDE(text) Q_OVERRIDE(text)
#define Q_ENUMS(x) Q_ENUMS(x)
#define Q_FLAGS(x) Q_FLAGS(x)
#define Q_ENUM(x) Q_ENUM(x)
#define Q_FLAGS(x) Q_FLAGS(x)
 /* qmake ignore Q_OBJECT */
#define Q_OBJECT Q_OBJECT
 /* qmake ignore Q_OBJECT */
#define Q_OBJECT_FAKE Q_OBJECT_FAKE
 /* qmake ignore Q_GADGET */
#define Q_GADGET Q_GADGET
#define Q_SCRIPTABLE Q_SCRIPTABLE
#define Q_INVOKABLE Q_INVOKABLE
#define Q_SIGNAL Q_SIGNAL
#define Q_SLOT Q_SLOT
#endif //Q_MOC_RUN

#define QML_PRIVATE_NAMESPACE \
    QT_PREPEND_NAMESPACE(QQmlPrivate)

#define QML_REGISTER_TYPES_AND_REVISIONS \
    QT_PREPEND_NAMESPACE(qmlRegisterTypesAndRevisions)

#define QML_ELEMENT \
    Q_CLASSINFO("QML.Element", "auto")

#define QML_ANONYMOUS \
    Q_CLASSINFO("QML.Element", "anonymous")

#define QML_NAMED_ELEMENT(NAME) \
    Q_CLASSINFO("QML.Element", #NAME)

#define QML_VALUE_TYPE(NAME) \
    Q_CLASSINFO("QML.Element", #NAME) \
    QML_UNCREATABLE("Value types cannot be created.")

#define QML_UNCREATABLE(REASON) \
    Q_CLASSINFO("QML.Creatable", "false") \
    Q_CLASSINFO("QML.UncreatableReason", REASON)

#define QML_SEQUENTIAL_CONTAINER(VALUE_TYPE) \
    Q_CLASSINFO("QML.Sequence", #VALUE_TYPE) \
    using QmlSequenceValueType = VALUE_TYPE; \
    enum class QmlIsSequence {yes = true}; \
    template<typename, typename> friend struct QML_PRIVATE_NAMESPACE::QmlSequence; \
    template<typename T, typename... Args> \
    friend void QML_REGISTER_TYPES_AND_REVISIONS(const char *uri, int versionMajor, QList<int> *);

#define QML_ADDED_IN_VERSION(MAJOR, MINOR) \
    Q_CLASSINFO("QML.AddedInVersion", Q_REVISION(MAJOR, MINOR))

#define QML_EXTRA_VERSION(MAJOR, MINOR) \
    Q_CLASSINFO("QML.ExtraVersion", Q_REVISION(MAJOR, MINOR))

#define QML_REMOVED_IN_VERSION(MAJOR, MINOR) \
    Q_CLASSINFO("QML.RemovedInVersion", Q_REVISION(MAJOR, MINOR))

#define QML_ATTACHED(ATTACHED_TYPE) \
    Q_CLASSINFO("QML.Attached", #ATTACHED_TYPE) \
    using QmlAttachedType = ATTACHED_TYPE; \
    template<class, class, bool> friend struct QML_PRIVATE_NAMESPACE::QmlAttached; \
    template<class> friend struct QML_PRIVATE_NAMESPACE::QmlAttachedAccessor;

#define QML_EXTENDED_NAMESPACE(EXTENDED_NAMESPACE) \
    Q_CLASSINFO("QML.Extended", #EXTENDED_NAMESPACE) \
    static constexpr const QMetaObject *qmlExtendedNamespace() { return &EXTENDED_NAMESPACE::staticMetaObject; } \
    template<class, class> friend struct QML_PRIVATE_NAMESPACE::QmlExtendedNamespace; \
    template<typename T, typename... Args> \
    friend void QML_REGISTER_TYPES_AND_REVISIONS(const char *uri, int versionMajor, QList<int> *);

#define QML_FOREIGN_NAMESPACE(FOREIGN_NAMESPACE) \
    Q_CLASSINFO("QML.Foreign", #FOREIGN_NAMESPACE)

#define QML_IMPLEMENTS_INTERFACES(INTERFACES) \
    Q_INTERFACES(INTERFACES) \
    enum class QmlIsInterface {yes = false}; \
    template<typename, typename> friend struct QML_PRIVATE_NAMESPACE::QmlInterface;

#define QML_CUSTOMPARSER Q_CLASSINFO("QML.HasCustomParser", "true")
)-";
