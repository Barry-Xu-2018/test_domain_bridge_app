#include "rclcpp/context.hpp"
#include "rclcpp/executors.hpp"
#include "rclcpp/node.hpp"

#include "composition_interfaces/srv/list_nodes.hpp"
#include "composition_interfaces/srv/load_node.hpp"
#include "composition_interfaces/srv/unload_node.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"
#include "lifecycle_msgs/srv/change_state.hpp"
#include "lifecycle_msgs/srv/get_available_states.hpp"
#include "lifecycle_msgs/srv/get_available_transitions.hpp"
#include "lifecycle_msgs/srv/get_state.hpp"
#include "rcl_interfaces/srv/describe_parameters.hpp"
#include "rcl_interfaces/srv/get_parameters.hpp"
#include "rcl_interfaces/srv/get_parameter_types.hpp"
#include "rcl_interfaces/srv/list_parameters.hpp"
#include "rcl_interfaces/srv/set_parameters.hpp"
#include "rcl_interfaces/srv/set_parameters_atomically.hpp"

#include "domain_bridge/domain_bridge.hpp"

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);

  domain_bridge::DomainBridge bridge;

  // For testing ros2 service command
  bridge.bridge_service<example_interfaces::srv::AddTwoInts>("/add_two_ints", 0, 1);

  // For testing ros2 param command
  bridge.bridge_service<rcl_interfaces::srv::DescribeParameters>("/parameter_blackboard/describe_parameters", 0, 1);
  bridge.bridge_service<rcl_interfaces::srv::GetParameterTypes>("/parameter_blackboard/get_parameter_types", 0, 1);
  bridge.bridge_service<rcl_interfaces::srv::GetParameters>("/parameter_blackboard/get_parameters", 0, 1);
  bridge.bridge_service<rcl_interfaces::srv::ListParameters>("/parameter_blackboard/list_parameters", 0, 1);
  bridge.bridge_service<rcl_interfaces::srv::SetParameters>("/parameter_blackboard/set_parameters", 0, 1);
  bridge.bridge_service<rcl_interfaces::srv::SetParametersAtomically>("/parameter_blackboard/set_parameters_atomically", 0, 1);

  // For testing ros2 component command
  bridge.bridge_service<composition_interfaces::srv::ListNodes>("/ComponentManager/_container/list_nodes", 0, 1);
  bridge.bridge_service<composition_interfaces::srv::LoadNode>("/ComponentManager/_container/load_node", 0, 1);
  bridge.bridge_service<composition_interfaces::srv::UnloadNode>("/ComponentManager/_container/unload_node", 0, 1);

  // For testing ros2 lifecycle command
  bridge.bridge_service<lifecycle_msgs::srv::ChangeState>("/lc_talker/change_state", 0, 1);
  bridge.bridge_service<lifecycle_msgs::srv::GetAvailableStates>("/lc_talker/get_available_states", 0, 1);
  bridge.bridge_service<lifecycle_msgs::srv::GetAvailableTransitions>("/lc_talker/get_available_transitions", 0, 1);
  bridge.bridge_service<lifecycle_msgs::srv::GetState>("/lc_talker/get_state", 0, 1);
  bridge.bridge_service<lifecycle_msgs::srv::GetAvailableTransitions>("/lc_talker/get_transition_graph", 0, 1);
  bridge.bridge_topic("/lc_talker/transition_event", "lifecycle_msgs/msg/TransitionEvent", 0, 1);

  rclcpp::executors::SingleThreadedExecutor executor;

  bridge.add_to_executor(executor);
  executor.spin();

  rclcpp::shutdown();
  return 0;
}
