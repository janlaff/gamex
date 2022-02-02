template<typename T>
Buffer<T> Buffer<T>::create(GLenum type, GLenum usage) {
    GLuint bufferId;
    glGenBuffers(1, &bufferId);

    return {bufferId, type, usage};
}

template<typename T>
GLuint Buffer<T>::getId() const {
    return id;
}

template<typename T>
GLenum Buffer<T>::getType() const {
    return type;
}

template<typename T>
GLenum Buffer<T>::getUsage() const {
    return usage;
}

template<typename T>
void Buffer<T>::bind() {
    glBindBuffer(type, id);
}

template<typename T>
void Buffer<T>::setData(const std::vector<T>& data) {
    bind();
    glBufferData(type, data.size() * sizeof(T), data.data(), usage);
}

template<typename T>
Buffer<T>::Buffer(GLuint id, GLenum type, GLenum usage)
    : id(id), type(type), usage(usage)
    {}
