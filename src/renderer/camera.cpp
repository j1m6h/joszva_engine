#include "../../inc/renderer/camera.h"

using joszva::engine::camera;

bool camera::moving()
{
    return keys.left || keys.right || keys.up || keys.down;
}

float camera::get_near_clip()
{
    return znear;
}

float camera::get_far_clip()
{
    return zfar;
}

void camera::set_perspective(float fov, float aspect, float znear, float zfar)
{
    this->fov = fov;
    this->znear = znear;
    this->zfar = zfar;
    matricies.perspective = glm::perspective(glm::radians(fov), aspect, znear, zfar);
    if (flip_y)
    {
        matricies.perspective[1][1] *= -1.0f;
    }
}

void camera::update_aspect_ratio(float aspect)
{
    matricies.perspective = glm::perspective(glm::radians(fov), aspect, znear, zfar);
    if (flip_y)
    {
        matricies.perspective[1][1] *= -1.0f;
    }
}

void camera::set_position(glm::vec3 position)
{
    this->position = position;
    update_view_matrix();
}

void camera::set_rotation(glm::vec3 rotation)
{
    this->rotation = rotation;
    update_view_matrix();
}

void camera::rotate(glm::vec3 delta)
{
    this->rotation += delta;
    update_view_matrix();
}

void camera::set_translation(glm::vec3 translation)
{
    this->position = translation;
    update_view_matrix();
}

void camera::translate(glm::vec3 delta)
{
    this->position += delta;
    update_view_matrix();
}

void camera::set_rotation_speed(float rotation_speed)
{
    this->rotation_speed = rotation_speed;
}

void camera::set_movement_speed(float movement_speed)
{
    this->movement_speed = movement_speed;
}

void camera::update(float delta_time)
{
    updated = false;
    if (type == camera_type::FIRSTPERSON)
    {
        if (moving())
        {
            glm::vec3 cam_front;
            cam_front.x = -cos(glm::radians(rotation.x)) * sin(glm::radians(rotation.y));
            cam_front.y = sin(glm::radians(rotation.x));
            cam_front.z = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
            cam_front = glm::normalize(cam_front);

            float move_speed = delta_time * movement_speed;

            if (keys.up)
                position += cam_front * move_speed;
            if (keys.down)
                position -= cam_front * move_speed;
            if (keys.left)
                position -= glm::normalize(glm::cross(cam_front, glm::vec3(0.0f, 1.0f, 0.0f))) * move_speed;
            if (keys.right)
                position += glm::normalize(glm::cross(cam_front, glm::vec3(0.0f, 1.0f, 0.0f))) * move_speed;

            update_view_matrix();
        }
    }
}

bool camera::update_pad(glm::vec2 axis_left, glm::vec2 axis_right, float delta_time)
{
    bool ret_val = false;

    if (type == camera_type::FIRSTPERSON)
    {
        const float dead_zone = 0.0015f;
        const float range = 1.0f - dead_zone;

        glm::vec3 cam_front;
        cam_front.x = -cos(glm::radians(rotation.x)) * sin(glm::radians(rotation.y));
        cam_front.y = sin(glm::radians(rotation.x));
        cam_front.z = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
        cam_front = glm::normalize(cam_front);

        float move_speed = delta_time * movement_speed * 2.0f;
        float rot_speed = delta_time * rotation_speed * 50.0f;

        /* move */
        if (fabsf(axis_left.y) > dead_zone)
        {
            float pos = (fabsf(axis_left.y) - dead_zone) / range;
            position -= cam_front * pos * ((axis_left.y < 0.0f) ? -1.0f : 1.0f) * move_speed;
            ret_val = true;
        }
        if (fabsf(axis_left.x) > dead_zone)
        {
            float pos = (fabsf(axis_left.x) - dead_zone) / range;
            position += glm::normalize(glm::cross(cam_front, glm::vec3(0.0f, 1.0f, 0.0f))) * pos * ((axis_left.x < 0.0f) ? -1.0f : 1.0f) * move_speed;
            ret_val = true;
        }

        /* rotate */
        if (fabsf(axis_right.x) > dead_zone)
        {
            float pos = (fabsf(axis_right.x) - dead_zone) / range;
            rotation.y += pos * ((axis_right.x < 0.0f) ? -1.0f : 1.0f) * rot_speed;
            ret_val = true;
        }

        if (fabsf(axis_right.y) > dead_zone)
        {
            float pos = (fabsf(axis_right.y) - dead_zone) / range;
            rotation.x -= pos * ((axis_right.y < 0.0f) ? -1.0f : 1.0f) * rot_speed;
            ret_val = true;
        }
    }

    if (ret_val)
    {
        update_view_matrix();
    }

    return ret_val;
}

void camera::update_view_matrix()
{
    glm::mat4 rot_m = glm::mat4(1.0f);
    glm::mat4 trans_m;

    rot_m = glm::rotate(rot_m, glm::radians(rotation.x * (flip_y ? -1.0f : 1.0f)), glm::vec3(1.0f, 0.0f, 0.0f));
    rot_m = glm::rotate(rot_m, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rot_m = glm::rotate(rot_m, glm::radians(rotation.y), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::vec3 translation = position;
    if (flip_y)
    {
        translation.y *= -1.0f;
    }

    trans_m = glm::translate(glm::mat4(1.0f), translation);

    switch (type)
    {
    case camera_type::FIRSTPERSON:
        matricies.view = rot_m * trans_m;
        break;
    case camera_type::LOOKAT:
        matricies.view = trans_m * rot_m;
        break;
    }

    view_pos = glm::vec4(position, 0.0f) * glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f);

    updated = true;
}