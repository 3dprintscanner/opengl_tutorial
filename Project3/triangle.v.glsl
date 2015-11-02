attribute vec3 v_color;
attribute vec3 coord3d;
varying vec3 f_color;
uniform mat4 m_transform;
uniform mat4 mvp;
void main(void) {
  gl_Position = mvp * m_transform * vec4(coord3d, 1.0);
  f_color = v_color;
}