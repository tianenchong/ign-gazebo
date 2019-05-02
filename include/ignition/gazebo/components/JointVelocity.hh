/*
 * Copyright (C) 2018 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef IGNITION_GAZEBO_COMPONENTS_JOINTVELOCITY_HH_
#define IGNITION_GAZEBO_COMPONENTS_JOINTVELOCITY_HH_

#include <ignition/msgs/double_v.pb.h>
#include <vector>

#include <ignition/gazebo/components/Factory.hh>
#include <ignition/gazebo/components/Component.hh>
#include <ignition/gazebo/config.hh>

namespace ignition
{
namespace gazebo
{
// Inline bracket to help doxygen filtering.
inline namespace IGNITION_GAZEBO_VERSION_NAMESPACE {
namespace components
{
  /// \brief Base class which can be extended to add serialization
  using JointVelocityBase = Component<std::vector<double>,
        class JointVelocityTag>;

  /// \brief Velocity of a joint's first axis in SI units (rad/s for revolute,
  /// m/s for prismatic).
  class JointVelocity : public JointVelocityBase
  {
    // Documentation inherited
    public: JointVelocity() : JointVelocityBase()
    {
    }

    // Documentation inherited
    public: explicit JointVelocity(const std::vector<double> &_data)
      : JointVelocityBase(_data)
    {
    }

    // Documentation inherited
    public: void Serialize(std::ostream &_out) const override
    {
      msgs::Double_V msg;
      *msg.mutable_data() = {this->Data().begin(), this->Data().end()};
      msg.SerializeToOstream(&_out);
    }

    // Documentation inherited
    public: void Deserialize(std::istream &_in) override
    {
      msgs::Double_V msg;
      msg.ParseFromIstream(&_in);

      this->Data() = {msg.data().begin(), msg.data().end()};
    }
  };

  IGN_GAZEBO_REGISTER_COMPONENT(
      "ign_gazebo_components.JointVelocity", JointVelocity)
}
}
}
}

#endif
