#ifndef HEXTOOLS_H
#define HEXTOOLS_H
#include <cmath>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/kernel/PointVector.h>

class HexTools
{
public:
    HexTools(){}
    // Converst point of hexagonal to regular lattice
    template <typename Type >
    static DGtal::PointVector<2, double> CartesianToHex ( const DGtal::PointVector<2, Type> & point )
    {
        return DGtal::PointVector<2, double>( point[0] * std::sqrt(3.)  + point[1] * std::sqrt(3.)/2.,
                                              point[1] * 3./2. );
    }

    // Converst point of regular lattice to hexagonal
    template <typename Type >
    static DGtal::PointVector<2, double> HexToCartesian ( const DGtal::PointVector<2, Type> & point )
    {
        return DGtal::PointVector<2, double>( point[0] * std::sqrt(3.)/3.  - point[1] * 1./3.,
                                              point[1] * 2./3. );
    }

    template <typename Type >
    static DGtal::PointVector<2, Type> CubeToAxial ( const DGtal::PointVector<3, Type> & point )
    {
        return DGtal::PointVector<2, Type>( point[0], point[2] );
    }

    template <typename Type >
    static DGtal::PointVector<3, Type> AxialToCube ( const DGtal::PointVector<2, Type> & point )
    {
        return DGtal::PointVector<3, Type>( point[0], -point[0] - point[1], point[1]);
    }

    //Hexagonal sampling for Axial coordinates
    template <typename Type >
    static DGtal::PointVector<2, Type> AxialRounding ( const DGtal::PointVector<2, Type> & point )
    {
        DGtal::PointVector<3, Type> cubePoint = AxialToCube( point );
        DGtal::PointVector<3, int> roundedCube ( std::round(cubePoint[0]), std::round(cubePoint[1]), std::round(cubePoint[2]) );
        DGtal::PointVector<3, double> diff( std::abs( cubePoint[0] - roundedCube[0] ), std::abs( cubePoint[1] - roundedCube[1] ),
                                            std::abs( cubePoint[2] - roundedCube[2] ) );

        if ( diff[0] > diff[1] && diff[0] > diff[2] )
            roundedCube[0] = -roundedCube[1] - roundedCube[2];
        else if (  diff[1] > diff[2] )
            roundedCube[1] = -roundedCube[0] - roundedCube[2];
        else
            roundedCube[2] = -roundedCube[0] - roundedCube[1];
        return CubeToAxial( roundedCube );
    }

    //Hexagonal sampling for Cube coordinates
    template <typename Type >
    static DGtal::PointVector<3, Type> CubeRounding ( const DGtal::PointVector<3, Type> & point )
    {
        DGtal::PointVector<3, int> roundedCube ( std::round ( point[0] ), std::round ( point[1] ), std::round ( point[2] ) );
        DGtal::PointVector<3, double> diff( std::abs( point[0] - roundedCube[0] ), std::abs( point[1] - roundedCube[1] ),
                                            std::abs( point[2] - roundedCube[2] ) );

        if (  diff[0] > diff[1] && diff[0] > diff[2] )
            roundedCube[0] = -roundedCube[1] - roundedCube[2];
        else if (  diff[1] > diff[2] )
            roundedCube[1] = -roundedCube[0] - roundedCube[2];
        else
            roundedCube[2] = -roundedCube[0] - roundedCube[1];
        return roundedCube;
    }

    static DGtal::PointVector<2, double> HexCorners(DGtal::PointVector<2, double> center, float size, uint index, bool pointTopped = true)
    {
        double angle_deg = 60. * index   + 30. * pointTopped;//+30 if point topped
        double angle_rad = M_PI / 180. * angle_deg;
        return DGtal::PointVector<2, double>(center[0] + size * std::cos(angle_rad), center[1] + size * std::sin(angle_rad));
    }
};

#endif // HEXTOOLS_H
