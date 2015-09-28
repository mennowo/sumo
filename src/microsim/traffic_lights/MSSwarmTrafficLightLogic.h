/****************************************************************************/
/// @file    MSSwarmTrafficLightLogic.h
/// @author  Gianfilippo Slager
/// @date    Mar 2010
/// @version $Id: MSSwarmTrafficLightLogic.h 0 2010-03-04 12:40:00Z gslager $
///
// The class for Swarm-based logics
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.dlr.de/
// Copyright 2001-2009 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/
#ifndef MSSwarmTrafficLightLogic_h
#define MSSwarmTrafficLightLogic_h

// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

//#define SWARM_DEBUG
#include <utils/common/SwarmDebug.h>
#include "MSSOTLHiLevelTrafficLightLogic.h"
#include "MSSOTLPhasePolicy.h"
#include "MSSOTLPlatoonPolicy.h"
#include "MSSOTLMarchingPolicy.h"
#include "MSSOTLCongestionPolicy.h"
#include "MSSOTLPolicy3DStimulus.h"
#include "MSSOTLPolicy5DFamilyStimulus.h"

template<class T>
class CircularBuffer
{
public:
  CircularBuffer(unsigned short size) :
      m_size(size), m_currentIndex(0), m_firstTime(true)
  {
    m_buffer = new T[m_size];
  }

  virtual ~CircularBuffer()
  {
    delete m_buffer;
  }

  bool addValue(const T newValue, T & replacedValue)
  {
    bool result = !m_firstTime;
    if (result)
      replacedValue = m_buffer[m_currentIndex];
    insert(newValue);
    return result;
  }

  void push_front(const T value)
  {
    insert(value);
  }

  T at(const unsigned short index) const
  {
    unsigned short idx = (m_currentIndex - 1 - index + m_size) % m_size;
    return m_buffer[idx];
  }

  T front() const
  {
    return at(0);
  }

  T back() const
  {
    return at(size()-1);
  }

  unsigned short size() const
  {
    if (m_firstTime)
      return m_currentIndex;
    return m_size;
  }

  void clear()
  {
    m_currentIndex = 0;
    m_firstTime = true;
  }

private:
  T * m_buffer;
  unsigned short m_size;
  unsigned short m_currentIndex;
  bool m_firstTime;

  inline void insert(const T & value)
  {
    m_buffer[m_currentIndex++] = value;
    if (m_currentIndex == m_size)
    {
      m_currentIndex = 0;
      m_firstTime = false;
    }
  }
};

class MSSwarmTrafficLightLogic: public MSSOTLHiLevelTrafficLightLogic {
public:
	//****************************************************
	/**
	 * @brief Constructor without sensors passed
     * @param[in] tlcontrol The tls control responsible for this tls
     * @param[in] id This tls' id
     * @param[in] subid This tls' sub-id (program id)
     * @param[in] phases Definitions of the phases
     * @param[in] step The initial phase index
     * @param[in] delay The time to wait before the first switch
	 * @param[in] parameters Parameters defined for the tll
	 */
	MSSwarmTrafficLightLogic(MSTLLogicControl &tlcontrol, const string &id,
			const string &subid, const Phases &phases, unsigned int step,
			SUMOTime delay,
			const std::map<std::string, std::string>& parameters);

	~MSSwarmTrafficLightLogic();

	/**
	 * @brief Initialises the tls with sensors on incoming and outgoing lanes
	 * Sensors are built in the simulation according to the type of sensor specified in the simulation parameter
	 * @param[in] nb The detector builder
	 * @exception ProcessError If something fails on initialisation
	 */
	void init(NLDetectorBuilder &nb) throw (ProcessError);

	int getMaxCongestionDuration() {
		std::ostringstream key;
		key << "MAX_CONGESTION_DUR";
		std::ostringstream def;
		def << "120";
		return (int) s2f(getParameter(key.str(), def.str()));
	}
	/*void setMaxCongestionDuration(unsigned int val) {
	 max_congestion_duration = val;
	 }*/

	double getPheroMaxVal() {
		std::ostringstream key;
		key << "PHERO_MAXVAL";
		std::ostringstream def;
		def << "10.0";
		return s2f(getParameter(key.str(), def.str()));
	}
	/*void setPheroMaxVal(double val) {
	 phero_maxval = val;
	 }*/
	double getBetaNo() {
		std::ostringstream key;
		key << "BETA_NO";
		std::ostringstream def;
		def << "0.99";
		return s2f(getParameter(key.str(), def.str()));
	}
	/*void setBetaNo(double val) {
	 beta_no = val;
	 }*/
	double getGammaNo() {
		std::ostringstream key;
		key << "GAMMA_NO";
		std::ostringstream def;
		def << "1.0";
		return s2f(getParameter(key.str(), def.str()));
	}
	/*void setGammaNo(double val) {
	 gamma_no = val;
	 }*/
	double getBetaSp() {
		std::ostringstream key;
		key << "BETA_SP";
		std::ostringstream def;
		def << "0.99";
		return s2f(getParameter(key.str(), def.str()));
	}
	/*void setBetaSp(double val) {
	 beta_sp = val;
	 }*/
	double getGammaSp() {
		std::ostringstream key;
		key << "GAMMA_SP";
		std::ostringstream def;
		def << "1.0";
		return s2f(getParameter(key.str(), def.str()));
	}
	/*void setGammaSp(double val) {
	 gamma_sp = val;
	 }*/
	double getChangePlanProbability() {
		std::ostringstream key;
		key << "CHANGE_PLAN_PROBABILITY";
		std::ostringstream def;
		def << "0.003";
		return s2f(getParameter(key.str(), def.str()));
	}
	/*void setChangePlanProbability(double val) {
	 change_plan_probability = val;
	 }*/
	double getThetaMax() {
		std::ostringstream key;
		key << "THETA_MAX";
		std::ostringstream def;
		def << "0.8";
		return s2f(getParameter(key.str(), def.str()));
	}
	/*void setThetaMax(double val) {
	 theta_max = val;
	 }*/
	double getThetaMin() {
		std::ostringstream key;
		key << "THETA_MIN";
		std::ostringstream def;
		def << "0.2";
		return s2f(getParameter(key.str(), def.str()));
	}
	/*void setThetaMin(double val) {
	 theta_min = val;
	 }*/

	double getThetaInit() {
			std::ostringstream key;
			key << "THETA_INIT";
			std::ostringstream def;
			def << "0.5";
			return s2f(getParameter(key.str(), def.str()));
		}

	double getLearningCox() {
		std::ostringstream key;
		key << "LEARNING_COX";
		std::ostringstream def;
		def << "0.0005";
		return s2f(getParameter(key.str(), def.str()));
	}
	/*void setLearningCox(double val) {
	 learning_cox = val;
	 }*/
	double getForgettingCox() {
		std::ostringstream key;
		key << "FORGETTING_COX";
		std::ostringstream def;
		def << "0.0005";
		return s2f(getParameter(key.str(), def.str()));
	}
	/*void setForgettingCox(double val) {
	 forgetting_cox = val;
	 }*/
	double getScaleFactorDispersionIn(){
		return scaleFactorDispersionIn;
	}

	double getScaleFactorDispersionOut(){
		return scaleFactorDispersionOut;
	}

	    /** @brief Returns the type of the logic as a string
     * @return The type of the logic
     */
    const std::string getLogicType() const {
        return "swarmBasedTrafficLogic";
    }
    /// @}
protected:

	/**
	 * \brief This pheronome is an indicator of congestion on input lanes.\n
	 * Its levels refer to the average speed of vehicles passing the input lane:
	 * the lower the speed the higher the pheromone.\n
	 * These levels are updated on every input lane, independently on lights state.
	 */
	MSLaneId_PheromoneMap pheromoneInputLanes;

	/**
	 * \brief This pheromone is an indicator of congestion on output lanes.\n
	 * Its levels refer to the average speed of vehicles passing the output lane:
	 * the lower the speed the higher the pheromone.\n
	 * These levels are updated on every output lane, independently on lights state.
	 */
	MSLaneId_PheromoneMap pheromoneOutputLanes;

	/**
	 * This member keeps track of the last thresholds update, s.t.
	 * updates can be correctly performed even on time-variable interations.
	 * @see MSSwarmTrafficLightLogic::updateSensitivities()
	 */
	SUMOTime lastThetaSensitivityUpdate;

	/*
	 * This member has to contain the switching logic for SOTL policies
	 */

	size_t decideNextPhase();

	bool canRelease();

	/*
	 * Computes how much time will pass after decideNextPhase will be executed again
	 */
	virtual SUMOTime computeReturnTime() {

		return DELTA_T;

	}

	/**
	 * @brief Resets pheromone levels
	 */
	void resetPheromone();

	/*
	 * @return The average pheromone level regarding congestion on input lanes
	 */
	double getPheromoneForInputLanes();

	/*
	 * @return The average pheromone level regarding congestion on output lanes
	 */
	double getPheromoneForOutputLanes();

	/*
	 * @return The dispersion level regarding congestion on input lanes
	 */
	double getDispersionForInputLanes(double average_phero_in);

	/*
	 * @return The dispersion level regarding congestion on output lanes
	 */
	double getDispersionForOutputLanes(double average_phero_out);

	/*
	 * @return The difference between the current max phero value and the average phero of the other lanes
	 */
	double getDistanceOfMaxPheroForInputLanes();

	/*
	 * @return The difference between the current max phero value and the average phero of the other lanes
	 */
	double getDistanceOfMaxPheroForOutputLanes();
	/**
	 * @brief Update pheromone levels
	 * Pheromone on input lanes is costantly updated
	 * Pheromone follows a discrete-time dynamic law "pheromone(k+1) = beta*pheromone(k) + gamma * sensed_val(k)"
	 */
	void updatePheromoneLevels();

	/**
	 * @brief Utility method to avoid code duplication
	 */
	void updatePheromoneLevels(MSLaneId_PheromoneMap &, std::string, const double, const double);

	/**
	 * After a policy has been chosen, for every iteration thresholds has to be updated.
	 * Thresholds reinforcement lowers the theta_sensitivity for the current policy and raises the ones for currently unused policies.
	 * Thresholds belongs to the interval [THETA_MIN THETA_MAX]
	 */
	void updateSensitivities();

	/**
	 * @brief Decide the current policy according to pheromone levels
	 * The decision reflects on currentPolicy value
	 */
	void decidePolicy();

	/**
	 * \brief Method that should calculate the valor of phi a coefficient to amplify/attenuate eta based on a factor.
	 * The factor depends on the situation when the function is called; should be the number of cars in the target lanes
	 * or the number of cars in the lanes with a red tl.
	 * @param[in] factor - the value to consider to compute this coefficient.
	 */
	double calculatePhi(int factor);

	/**
	 * \brief Method that should calculate the valor of eta a coefficient to evaluate the current
	 * policy's work. This eta is based on the difference between the number of vehicles that enters a tl
	 * and the ones that exit it. It consider vehicles on a lane with a tl set to red as well to determinate
	 * policy work.
	 */
	double calculateEtaDiff();

	double calculateEtaRatio();

	/*
	 * \brief Method to reset the map that stores if a lane is already been checked during the
	 * evaluation of eta.
	 */
	void resetLaneCheck();
	void choosePolicy(double phero_in, double phero_out, double dispersion_in, double dispersion_out);
	void choosePolicy(double phero_in, double phero_out);

	std::string getPoliciesParam() {
		std::ostringstream key;
		key << "POLICIES";
		std::ostringstream def;
		def << "Platoon;Phase;Marching;Congestion";
		return getParameter(key.str(), def.str());
	}

	/*
	 * Reinforcement modes:
	 * 0-> elapsed time
	 * 1-> diff
	 * 2-> ratio
	 */
	unsigned int getReinforcementMode() {
		std::ostringstream key;
		key << "REIMODE";
		std::ostringstream def;
		def << "0";
		return s2f(getParameter(key.str(), def.str()));
	}

	void initScaleFactorDispersionIn(int lanes_in){
		std::vector<double> phero_values;

		for(int i=0; i<lanes_in/2; i++){
			phero_values.push_back(getPheroMaxVal());
		}
		for(int i=lanes_in/2; i<lanes_in; i++){
					phero_values.push_back(0.0);
		}

		double sum_avg_tmp = 0;

		for(int i=0; i<phero_values.size(); i++){
					sum_avg_tmp += phero_values[i];
		}

		double mean = sum_avg_tmp / phero_values.size();

		double sum_dev_tmp = 0;
		for(int i=0; i<phero_values.size(); i++){
					sum_dev_tmp += pow(phero_values[i] - mean, 2);
		}

		double deviation = sqrt(sum_dev_tmp/ phero_values.size());

		scaleFactorDispersionIn = getPheroMaxVal() / deviation;
	}

	void initScaleFactorDispersionOut(int lanes_out){
		std::vector<double> phero_values;

				for(int i=0; i<lanes_out/2; i++){
					phero_values.push_back(getPheroMaxVal());
				}
				for(int i=lanes_out/2; i<lanes_out; i++){
							phero_values.push_back(0.0);
				}

				double sum_avg_tmp = 0;
				for(int i=0; i<phero_values.size(); i++){
							sum_avg_tmp += phero_values[i];
				}
				double mean = sum_avg_tmp / phero_values.size();

				double sum_dev_tmp = 0;

				for(int i=0; i<phero_values.size(); i++){
							sum_dev_tmp += pow(phero_values[i] - mean, 2);
				}

				double deviation = sqrt(sum_dev_tmp/ phero_values.size());

				scaleFactorDispersionOut = getPheroMaxVal() / deviation;
	}

	/**
	 * @brief Check if a lane is allowed to be added to the maps pheromoneInputLanes and pheromoneOutputLanes
	 * Control in this function if the lane is a walking area, a crossing, or if only pedestrian are allowed.
	 * Return true if the lane has to be added, false otherwise.
	 */
	bool allowLine(MSLane * );

	bool logData;
	ofstream swarmLogFile;
	/**
	 * \brief When true, indicates that the current policy MUST be changed.\n
	 * It's used to force the exit from the congestion policy
	 */
	bool mustChange;
	unsigned int congestion_steps;

	/**
	 * \brief Map to check if a lane was already controlled during the elaboration of eta.
	 */
	LaneCheckMap laneCheck;
	/**
	 * \brief A copy of the target lanes of this phase.
	 */
	LaneIdVector targetLanes;
	/**
	 * \brief When true indicates that we can skip the evaluation of eta since we've
	 * a congestion policy that is lasting too much.
	 */
	bool skipEta;
	/**
	 * \brief When true indicates that we've already acquired the target lanes for this
	 * particular phase.
	 */
	bool gotTargetLane;

	int carsIn;
	int carsOut;
	int inTarget;
	int notTarget;
	/**
	 * \factors to scale pheromoneDispersion in range [0, 10]
	 */
	double scaleFactorDispersionIn;
	double scaleFactorDispersionOut;

//	For every lane its index. Esed to get the current lane state for the lane
	std::map<std::string, std::vector<int> > m_laneIndexMap;
	std::string getLaneLightState(const std::string & laneId);
//	store the last message logged. if equal do not log it again
	std::map<std::string, std::string> m_pheroLevelLog;

	//derivative
	std::map<std::string, CircularBuffer<double>* > m_meanSpeedHistory;
	std::map<std::string, CircularBuffer<double>* > m_derivativeHistory;
	double m_derivativeAlpha;
	int m_losCounter;//los: loss of signal
	int m_losMaxLimit;
	bool m_useVehicleTypesWeights;

//	double pheroBegin;
};




#endif
/****************************************************************************/
