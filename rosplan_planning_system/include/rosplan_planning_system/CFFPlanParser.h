#include "ros/ros.h"
#include "std_srvs/Trigger.h"
#include "diagnostic_msgs/KeyValue.h"
#include "mongodb_store/message_store.h"
#include "rosplan_knowledge_msgs/KnowledgeItem.h"
#include "rosplan_knowledge_msgs/KnowledgeUpdateService.h"
#include "rosplan_dispatch_msgs/ActionDispatch.h"
#include "rosplan_knowledge_msgs/Notification.h"
#include "rosplan_knowledge_msgs/Filter.h"
#include "PlanningEnvironment.h"
#include "PlanParser.h"
#include "EsterelPlan.h"

#ifndef KCL_cff_plan_parser
#define KCL_cff_plan_parser

namespace KCL_rosplan {

	/* Plan Parsing class definition */
	class CFFPlanParser: public PlanParser
	{

	private:
		
		// ROS node handle.
		ros::NodeHandle* node_handle;
		
		// Scene database
		mongodb_store::MessageStoreProxy message_store;

		// Knowledge base
		ros::ServiceClient update_knowledge_client;

		void toLowerCase(std::string &str);
		void preparePDDLConditions(StrlNode &node, PlanningEnvironment &environment);

	public:

		/* plan description in Esterel */
		std::map<std::string,StrlNode> plan_nodes;
		std::map<std::string,StrlEdge> plan_edges;
		std::map<std::string,rosplan_knowledge_msgs::KnowledgeItem> edge_conditions;

		/* constructor */
		CFFPlanParser(ros::NodeHandle &nh);

		/* service to parse plans */
		bool produceEsterel();

		/* virtual methods */
		void reset();
		void preparePlan(std::string &dataPath, PlanningEnvironment &environment, size_t freeActionID);
		void generateFilter(PlanningEnvironment &environment);
	};
}
#endif
