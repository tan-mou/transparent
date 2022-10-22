#include"Texture2.h"
Texture2::Texture2(unsigned int texture_position, std::string texture_source,unsigned int type) {
    glGenTextures(1, &texture_id);
    glActiveTexture(texture_position);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    // Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // ���ز���������
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texture_source.c_str(), &width, &height, &nrChannels, 0);
    if (type == JPG) {
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }
    else if (type == PNG) {
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }
    else {
        std::cout << "Image type error" << std::endl;
        __debugbreak();
    }
    

}
void Texture2::Bind() {
    glBindTexture(GL_TEXTURE_2D, texture_id);
}
void Texture2::UnBind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
