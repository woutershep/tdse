/*
Copyright (C) 2016 Jeremy Starnes

This file is part of TDSE.

TDSE is free software: you can redistribute it and/or modify it under the terms
of the GNU Affero General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

TDSE is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along
with TDSE; see the file COPYING. If not, see <http://www.gnu.org/licenses/agpl>
*/
#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED


#include "physics.h"


class projectile
{
public:
  class properties
  {
  public:
    properties(float mass_);

    float mass;
  };

  projectile(const properties & type_,
             const glm::vec2 & position_,
             const glm::vec2 & velocity_);
  projectile(const projectile & other);
  projectile & operator=(const projectile & rhs) = delete;

  // Returns true on collision, otherwise false
  bool step(btCollisionWorld & world, float_seconds step);

  const properties & type;
  const glm::vec2 & position;
  const glm::vec2 & velocity;

private:
  glm::vec2 position__, velocity__;
};


class hit_info
{
public:
  hit_info(const projectile::properties & t, const glm::vec2 & v,
           const glm::vec2 & p, const glm::vec2 & n);

  const projectile::properties & type;
  glm::vec2 velocity;
  glm::vec2 world_point;
  glm::vec2 world_normal;
};


class needs_hit
{
public:
  virtual void hit(const hit_info & info) = 0;
};


#include <list>
class shooter : public needs_presubstep
{
public:
  shooter(float_seconds fire_period_);
  shooter(const shooter & other);
  shooter & operator=(const shooter & rhs) = delete;

  virtual projectile fire() = 0;

  bool wants_fire;
  float_seconds fire_period;
  const float_seconds & cooldown;
  std::list<projectile> projectiles;

private:
  float_seconds cooldown_;
  void presubstep(bullet_world & world, float_seconds substep_time) override;
};


#endif  // PROJECTILE_H_INCLUDED
