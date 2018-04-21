#pragma once
#include <Eigen/Core>
#include <vector>

namespace igl
{
	namespace viewer
	{
		class Viewer;
	}
}

class LagrangianMesh
{
private:
	igl::viewer::Viewer * viewer_;

	Eigen::MatrixX3d colors_;

	Eigen::MatrixX3d elementRestDirections_1_;
	Eigen::MatrixX3d elementRestDirections_2_;
	Eigen::MatrixX3d elementRestDirections_3_;

	void buildFaceWings_();
	void computeRestMetrics_();
	void computeAreas_();

public:
	Eigen::MatrixX3d vertexPositions;
	Eigen::MatrixX3d elementPositions;
	Eigen::MatrixX3d vertexVelocities;
	Eigen::MatrixX3d elementVelocities;

	Eigen::VectorXd vertexMasses;
	Eigen::VectorXd elementMasses;
	Eigen::VectorXd vertexVolumes;
	Eigen::VectorXd elementVolumes;

	Eigen::MatrixX3d vertexAffineMomenta_1;
	Eigen::MatrixX3d vertexAffineMomenta_2;
	Eigen::MatrixX3d vertexAffineMomenta_3;

	Eigen::MatrixX3d elementAffineMomenta_1;
	Eigen::MatrixX3d elementAffineMomenta_2;
	Eigen::MatrixX3d elementAffineMomenta_3;

	Eigen::MatrixX3i faces;
	Eigen::MatrixX3i faceWings;

	Eigen::VectorXd areas;
	std::vector< Eigen::Matrix2d> inverseMetrics;

	std::vector<Eigen::Matrix3d> plasticDeformationGradient;
	std::vector<Eigen::Matrix3d> elasticDeformationGradient;

	double mu;
	double lambda;
	
	double shearStiffness;
	double stiffness;

	double frictionCoeff;

	LagrangianMesh(const Eigen::MatrixX3d& vertexPositions,
		const Eigen::MatrixX3i& faces,
		const Eigen::MatrixX3d& vertexVelocities,
		const Eigen::MatrixX3d& elementVelocities,
		const std::vector<Eigen::Matrix3d>& elasticDeformationGradient,
		const std::vector<Eigen::Matrix3d>& plasticDeformationGradient,
		const Eigen::VectorXd& vertexMasses,
		const Eigen::VectorXd& vertexVolumes,
		const Eigen::VectorXd& elementMasses,
		const Eigen::VectorXd& elementVolumes,
		const Eigen::MatrixX3d& elementRestDirections_1,
		const Eigen::MatrixX3d& elementRestDirections_2,
		const Eigen::MatrixX3d& elementRestDirections_3,
		double mu,
		double lambda,
		double shearStiffness,
		double stiffness,
		double frictionCoeff);

	static LagrangianMesh ObjMesh(const std::string& filename,
		double density,
		double thickness,
		double youngsModulus,
		double poissonRatio,
		double shearStiffness,
		double stiffness,
		double frictionAngleInDegree);

	void bindViewer(igl::viewer::Viewer * viewer) { viewer_ = viewer; }
	void updateViewer();
	void updateElementPositions();
	void filterOutConstrainedVertices();

	const Eigen::MatrixX3d& elementRestDirections_1() const { return elementRestDirections_1_; }
	const Eigen::MatrixX3d& elementRestDirections_2() const { return elementRestDirections_2_; }
	const Eigen::MatrixX3d& elementRestDirections_3() const { return elementRestDirections_3_; }

	void computeVertexInPlaneForces(Eigen::MatrixX3d & vertexForces,
		std::vector < Eigen::Matrix2d > & inPlanePiolaKirhoffStresses);
};