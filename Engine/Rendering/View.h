#ifndef VIEW
#define VIEW

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class View {
public:
    View();
    glm::mat4 getMatrix();
protected:
    glm::mat4 projection_matrix;
};

class PerspectiveView : public View {
public:
    PerspectiveView(float view_angle, float ratio, float near_clip, float far_clip);
};

class OrthogonalView : public View {
public:
    OrthogonalView();
};

#endif
