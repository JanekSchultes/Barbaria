#include "View.h"
    
std::mutex view_lock;

View::View() {

}

PerspectiveView::PerspectiveView(float view_angle, float ratio, float near_clip, float far_clip) {
    projection_matrix = glm::mat4(1.0f);
    projection_matrix = glm::perspective(glm::radians(view_angle), ratio, near_clip, far_clip);
}

glm::mat4 View::getMatrix() {
    glm::mat4 tmp;
    view_lock.lock();
    tmp = projection_matrix;
    view_lock.unlock();
    return tmp;
}

OrthogonalView::OrthogonalView() {
    projection_matrix = glm::mat4(1.0f);
}
