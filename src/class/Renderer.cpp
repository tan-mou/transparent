#include"Renderer.h"
void GLClearError() {
    while (glGetError() != GL_NO_ERROR);

}

bool GLLogCall(const char* function, const char* file, int line) {

    while (GLenum error = glGetError()) {//�������е㶫���ģ�����Ѵ��󶼷��ظ�errorֱ��glgeterror����gl_no_error
        std::cout << "[OpenGL_Error(" << error << ")]" << ":" << function << "\t" << "line:" << line << std::endl;
        return false;
    }
    return true;
}