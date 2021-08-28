#ifndef CAMERA_H
#define CAMERA_H

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/quaternion.hpp>

namespace joszva::engine
{
    class camera
    {
    public:
        bool moving();
        float get_near_clip();
        float get_far_clip();
        void set_perspective(float fov, float aspect, float znear, float zfar);
        void update_aspect_ratio(float aspect);
        void set_position(glm::vec3 position);
        void set_rotation(glm::vec3 rotation);
        void rotate(glm::vec3 delta);
        void set_translation(glm::vec3 translation);
        void translate(glm::vec3 delta);
        void set_rotation_speed(float rotation_speed);
        void set_movement_speed(float movement_speed);
        void update(float delta_time);
        /* update camera passing seperate axis data */
        bool update_pad(glm::vec2 axis_left, glm::vec2 axis_right, float delta_time);

    private:
        enum camera_type
        {
            LOOKAT,
            FIRSTPERSON
        };

        struct
        {
            glm::mat4 perspective;
            glm::mat4 view;
        } matricies;

        struct 
        {
            bool left = false;
            bool right = false;
            bool up = false;
            bool down = false;
        } keys;

        void update_view_matrix();

        float fov;
        float znear;
        float zfar;

        glm::vec3 rotation = glm::vec3();
        glm::vec3 position = glm::vec3();
        glm::vec4 view_pos = glm::vec4();

        float rotation_speed = 1.0f;
        float movement_speed = 1.0f;

        bool updated = false;
        bool flip_y = false;

        camera_type type = camera_type::LOOKAT;
    };
}
#endif