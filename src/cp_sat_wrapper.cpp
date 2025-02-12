#include <iostream>

#include <ortools/sat/cp_model.h>

namespace sat = operations_research::sat;

extern "C" unsigned char*
cp_sat_wrapper_solve(
    unsigned char* model_buf,
    size_t model_size,
    size_t* out_size)
{
    sat::CpModelProto model;
    bool res = model.ParseFromArray(model_buf, model_size);
    assert(res);

    sat::CpSolverResponse response = sat::Solve(model);

    *out_size = response.ByteSizeLong();
    unsigned char* out_buf = (unsigned char*) malloc(*out_size);
    res = response.SerializeToArray(out_buf, *out_size);
    assert(res);

    return out_buf;
}

 extern "C" unsigned char*
 cp_sat_wrapper_solve_with_parameters(
     unsigned char* model_buf,
     size_t model_size,
     unsigned char* params_buf,
     size_t params_size,
     size_t* out_size)
 {
    sat::CpModelProto model;
    bool res = model.ParseFromArray(model_buf, model_size);
    assert(res);

    sat::SatParameters params;
    res = params.ParseFromArray(params_buf, params_size);
    assert(res);

    sat::CpSolverResponse response = sat::SolveWithParameters(model, params);

    *out_size = response.ByteSizeLong();
    unsigned char* out_buf = (unsigned char*) malloc(*out_size);
    res = response.SerializeToArray(out_buf, *out_size);
    assert(res);

    return out_buf;
}

extern "C" char*
cp_sat_wrapper_cp_model_stats(unsigned char* model_buf, size_t model_size) {
    sat::CpModelProto model;
    const bool res = model.ParseFromArray(model_buf, model_size);
    assert(res);

    const std::string stats = sat::CpModelStats(model);
    return strdup(stats.c_str());
}

extern "C" char*
cp_sat_wrapper_cp_solver_response_stats(
    unsigned char* response_buf,
    size_t response_size,
    bool has_objective)
{
    sat::CpSolverResponse response;
    const bool res = response.ParseFromArray(response_buf, response_size);
    assert(res);

    const std::string stats = sat::CpSolverResponseStats(response, has_objective);
    return strdup(stats.c_str());
}
