/*************************************************************************
*  Copyright (C) 2006 by Bruno Chareyre                                  *
*  bruno.chareyre@hmg.inpg.fr                                            *
*                                                                        *
*  This program is free software; it is licensed under the terms of the  *
*  GNU General Public License v2 or later. See file LICENSE for details. *
*************************************************************************/


#ifndef TRIAXIALCOMPRESSIONENGINE_HPP
#define TRIAXIALCOMPRESSIONENGINE_HPP

#include<yade/core/DeusExMachina.hpp>
#include <Wm3Vector3.h>
#include<yade/lib-base/yadeWm3.hpp>
#include "TriaxialStressController.hpp"
#include <string>

/*! \brief Isotropic compression + uniaxial compression test

	detailed description...
 */

class PhysicalAction;

class TriaxialCompressionEngine : public TriaxialStressController
{
	private :
		shared_ptr<PhysicalAction> actionForce;
		
	public :
		TriaxialCompressionEngine();
		virtual ~TriaxialCompressionEngine();
		
		//! Strain velocity (./s)
		Real strainRate;
		Real currentStrainRate;
		//! Max ratio of resultant forces on mean contact force
		Real UnbalancedForce;
		//! Value of UnbalancedForce for which the system is considered stable
		Real StabilityCriterion;
		Vector3r strain;
		Vector3r translationAxis;
		//! is isotropicInternalCompactionFinished?
		bool Phase1;
		int FinalIterationPhase1, Iteration;
		std::string Phase1End; //,Phase2End;
		//! Is uniaxial compression currently activated?
		bool compressionActivated;
		//! Auto-switch between isotropic and uniaxial compression?
		bool autoCompressionActivation;
				
		virtual void applyCondition(Body * body);
		void updateParameters(Body * body);
		//! Compute the mean/max unbalanced force in the assembly (normalized by mean contact force)
    		Real ComputeUnbalancedForce(Body * body, bool maxUnbalanced=false);

	protected :
		virtual void postProcessAttributes(bool);
		virtual void registerAttributes();
	REGISTER_CLASS_NAME(TriaxialCompressionEngine);
	REGISTER_BASE_CLASS_NAME(TriaxialStressController);
};

REGISTER_SERIALIZABLE(TriaxialCompressionEngine,false);

#endif //  TRIAXIALCOMPRESSIONENGINE_HPP
