#ifndef HX3D_PHYSICS_2D_MANIFOLD
#define HX3D_PHYSICS_2D_MANIFOLD

#include "hx3d/physics/2d/polygon.hpp"
#include "hx3d/physics/2d/circle.hpp"

namespace hx3d {
namespace physics2d {

class Manifold;
bool checkCollisions(Manifold& m, Ptr<Circle> a, Ptr<Circle> b);
bool checkCollisions(Manifold& m, Ptr<Polygon> a, Ptr<Circle> b);
bool checkCollisions(Manifold& m, Ptr<Circle> a, Ptr<Polygon> b);
bool checkCollisions(Manifold& m, Ptr<Polygon> a, Ptr<Polygon> b);

class Manifold {
public:
  Ptr<Collider> a;
  Ptr<Collider> b;

  float penetration;
  glm::vec2 normal;
  std::vector<glm::vec2> contacts;

  float mixedRestitution; // e
  float mixedDynamicFriction; // df
  float mixedStaticFriction; // sf

  ///////////

  Manifold(Ptr<Collider> a, Ptr<Collider> b): a(a), b(b) {
    penetration = 0.f;
    normal = {0, 0};
    mixedRestitution = 0.f;
    mixedDynamicFriction = 0.f;
    mixedStaticFriction = 0.f;
  }

  bool solve() {
    bool value = false;

    if (a->shape == Collider::Shape::Circle && b->shape == Collider::Shape::Circle)
      value = checkCollisions(*this, std::dynamic_pointer_cast<Circle>(a), std::dynamic_pointer_cast<Circle>(b));
    else if (a->shape == Collider::Shape::Circle && b->shape == Collider::Shape::Polygon)
      value = checkCollisions(*this, std::dynamic_pointer_cast<Polygon>(b), std::dynamic_pointer_cast<Circle>(a));
    else if (a->shape == Collider::Shape::Polygon && b->shape == Collider::Shape::Circle)
      value = checkCollisions(*this, std::dynamic_pointer_cast<Polygon>(a), std::dynamic_pointer_cast<Circle>(b));
    else if (a->shape == Collider::Shape::Polygon && b->shape == Collider::Shape::Polygon)
      value = checkCollisions(*this, std::dynamic_pointer_cast<Polygon>(a), std::dynamic_pointer_cast<Polygon>(b));

    return value;
  }

  void initialize() {
    mixedRestitution = std::min(a->material.restitution, b->material.restitution);
    mixedStaticFriction = std::sqrt(a->material.staticFriction * b->material.staticFriction);
    mixedDynamicFriction = std::sqrt(a->material.dynamicFriction * b->material.dynamicFriction);

    for (unsigned int i = 0; i < contacts.size(); ++i) {
      glm::vec2 ra = contacts[i] - a->position;
      glm::vec2 rb = contacts[i] - b->position;

      glm::vec2 rv = b->velocity + math::cross(b->angularVelocity, rb) - a->velocity - math::cross(a->angularVelocity, ra);

      if (math::squareLength(rv) < 5) {
        mixedRestitution = 0;
      }
    }
  }

  void applyImpulse() {
    if (a->massData.invMass + b->massData.invMass == 0) {
      infiniteMassCorrection();
      return;
    }

    for (unsigned int i = 0; i < contacts.size(); ++i) {
      glm::vec2 ra = contacts[i] - a->position;
      glm::vec2 rb = contacts[i] - b->position;

      glm::vec2 rv = b->velocity + math::cross(b->angularVelocity, rb) - a->velocity - math::cross(a->angularVelocity, ra);

      float contactVelocity = glm::dot(rv, normal);
      if (contactVelocity > 0)
        return;

      float raCross = std::max(math::cross(ra, normal), 0.f);
      float rbCross = std::max(math::cross(rb, normal), 0.f);

      float invMassSum = a->massData.invMass + b->massData.invMass + std::sqrt(raCross) * a->massData.invInertia + std::sqrt(rbCross) * b->massData.invInertia;

      float j = -(1.f + mixedRestitution) * contactVelocity;
      j /= invMassSum;
      j /= (float)contacts.size();

      glm::vec2 impulse = normal * j;
      a->applyImpulse(-impulse, ra);
      b->applyImpulse(impulse, rb);

      rv = b->velocity + math::cross(b->angularVelocity, rb) - a->velocity - math::cross(a->angularVelocity, ra);

      glm::vec2 nRv = rv - (normal * glm::dot(rv, normal));
      glm::vec2 t = math::normalize(nRv);

      float jt = -glm::dot(rv, t);
      jt /= invMassSum;
      jt /= (float)contacts.size();

      if (jt == 0.f)
        return;

/*
      glm::vec2 tangentImpulse;
      if (std::abs(jt) < j * mixedStaticFriction)
        tangentImpulse = t * jt;
      else
        tangentImpulse = t * -j * mixedDynamicFriction;

      a->applyImpulse(-tangentImpulse, ra);
      b->applyImpulse(tangentImpulse, rb);
      */
    }
  }

  void positionalCorrection() {
    const float kSlop = 0.05f;
    const float percent = 0.4f;
    glm::vec2 correction = (std::max(penetration - kSlop, 0.f) / (a->massData.invMass + b->massData.invMass)) * normal * percent;

    a->position -= correction * a->massData.invMass;
    b->position += correction * b->massData.invMass;
  }

  void infiniteMassCorrection() {
    a->velocity = {0, 0};
    b->velocity = {0, 0};
  }
};

}
}

#include "hx3d/physics/2d/collisions.hpp"

#endif
