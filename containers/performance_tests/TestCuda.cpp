/*
//@HEADER
// ************************************************************************
//
//                        Kokkos v. 3.0
//       Copyright (2020) National Technology & Engineering
//               Solutions of Sandia, LLC (NTESS).
//
// Under the terms of Contract DE-NA0003525 with NTESS,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Christian R. Trott (crtrott@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#include <Kokkos_Macros.hpp>
#if defined(KOKKOS_ENABLE_CUDA)

#include <cstdint>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

#include <gtest/gtest.h>

#include <Kokkos_Core.hpp>

#include <TestDynRankView.hpp>

#include <Kokkos_UnorderedMap.hpp>

#include <TestGlobal2LocalIds.hpp>

#include <TestUnorderedMapPerformance.hpp>

namespace Performance {

class cuda : public ::testing::Test {
 protected:
  static void SetUpTestCase() {
    std::cout << std::setprecision(5) << std::scientific;
    Kokkos::InitArguments args(-1, -1, 0);
    Kokkos::initialize(args);
  }
  static void TearDownTestCase() { Kokkos::finalize(); }
};

TEST_F(cuda, dynrankview_perf) {
  std::cout << "Cuda" << std::endl;
  std::cout << " DynRankView vs View: Initialization Only " << std::endl;
  test_dynrankview_op_perf<Kokkos::Cuda>(40960);
}

TEST_F(cuda, global_2_local) {
  std::cout << "Cuda" << std::endl;
  std::cout << "size, create, generate, fill, find" << std::endl;
  for (unsigned i = Performance::begin_id_size; i <= Performance::end_id_size;
       i *= Performance::id_step)
    test_global_to_local_ids<Kokkos::Cuda>(i);
}

TEST_F(cuda, unordered_map_performance_near) {
  Perf::run_performance_tests<Kokkos::Cuda, true>("cuda-near");
}

TEST_F(cuda, unordered_map_performance_far) {
  Perf::run_performance_tests<Kokkos::Cuda, false>("cuda-far");
}

}  // namespace Performance
#else
void KOKKOS_CONTAINERS_PERFORMANCE_TESTS_TESTCUDA_PREVENT_EMPTY_LINK_ERROR() {}
#endif /* #if defined( KOKKOS_ENABLE_CUDA ) */
